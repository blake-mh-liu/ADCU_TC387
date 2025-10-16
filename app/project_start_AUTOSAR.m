function project_start_AUTOSAR
%% Initial settings
TargetECU_Abb = 'MCU';
code_generate = boolean(0);
ModelCreate = boolean(0);
ModelUpdate = boolean(0);
project_path = pwd;

%% License check and add path
if code_generate && ~license('checkout','Matlab_Coder')
    error('Error: No Matlab_Coder license'); 
end

if ~license('checkout','Simulink')
    error('Error: No Simulink license');
end

if ~license('checkout','Stateflow')
    error('Error: No Stateflow license');
end

cd(project_path);
addpath(project_path);
addpath([project_path '/Scripts']);
addpath([project_path '/library']);
addpath([project_path '/library/GRC_Lib']);
addpath([project_path '/library/GRC_Lib/LibPic']);
addpath([project_path '/documents/A2L_Head']);
addpath([project_path '/documents/FVT_API']);
arch_path = [project_path '/software/sw_development/arch'];
addpath(arch_path);
cd(arch_path);

files = dir(fullfile(arch_path, '*.slx'));
swcTypes = {};
for i = 1:length(files)
    fileName = files(i).name;
    if contains(fileName, '_type.slx')
        modelName = strrep(fileName, '_type.slx', '');
        swcTypes{end+1, 1} = modelName;
    end    
end
swcTypes{end+1, 1} = 'Comp_FDC_main';


%% load arxml and vcu_local
% if ModelCreate
%     cd ([project_path '/documents/ARXML_output']);
%     A = dir;
%     cnt = 0;
% 
%     for i = 1:length(A)
%         if contains(A(i).name,'.arxml')
%             cnt = cnt+1;
%             k{cnt} = A(i).name;
%         else
%             continue
%         end
%     end
% 
%     ar = arxml.importer(k);
%     cd(arch_path);
%     Simulink.data.dictionary.closeAll;
%     if ModelUpdate
%         model = ['Comp_' TargetECU_Abb '_main'];
%         open_system(model)
%         updateModel(ar, model)
%     else
%         createCompositionAsModel(ar, ['/Comp_' TargetECU_Abb '_ARPkg/Comp_' TargetECU_Abb '_main'], ...
%             'ModelPeriodicRunnablesAs', 'FunctionCallSubsystem', 'DataDictionary', 'APPTypes.sldd');
%     end
%     DictionaryObj = Simulink.data.dictionary.open('APPTypes.sldd');
%     saveChanges(DictionaryObj);
% 
%     if ~ModelUpdate
%         % SWC_ETE_type Autobuild
%         cd(arch_path)
%         %FVT_SWC_Autobuild_D21()
%     end
% end
if ModelCreate || ModelUpdate
    cd ([project_path '/documents/ARXML_output']);
    A = dir;
    cnt = 0;
    [indx, q] = listdlg('PromptString',{'Select the SWC you want to update/create.'},'ListSize',[250,500],'ListString',swcTypes);
    if q == 0; return; end
    for i = 1:length(indx)
        swcTypes(i,1) = swcTypes(indx(i),1);
    end
    swcTypes((length(indx)+1):end) = [];
    for i = 1:length(A)
        if contains(A(i).name,'.arxml')
            cnt = cnt+1;
            k{cnt} = A(i).name;
        else
            continue
        end
    end

    ar = arxml.importer(k);
    cd(arch_path);
    Simulink.data.dictionary.closeAll;
    cleanupObj = onCleanup(@() cleanupSldd());
    for i =1:length(swcTypes(:,1))
        if ModelUpdate
            cd(arch_path);
            ModelName = [char(swcTypes(i)) '_type'];
            open_system(ModelName);
            updateModel(ar, ModelName);
            Modify_APPType_sldd();
	    else
            evalin( 'base', 'clear B*_outputs');
            ModelName = char(swcTypes(i));
            if contains(swcTypes(i),'Comp_FDC_main')
	            createCompositionAsModel(ar, ['/Comp_' TargetECU_Abb '_ARPkg/Comp_' TargetECU_Abb '_main'], ...
	            'ModelPeriodicRunnablesAs', 'FunctionCallSubsystem', 'DataDictionary', 'APPTypes.sldd');
            else
                createComponentAsModel(ar, ['/' ModelName '_ARPkg/' ModelName '_type'], ...
                'ModelPeriodicRunnablesAs', 'FunctionCallSubsystem', 'DataDictionary', 'APPTypes.sldd');
            end
            Modify_APPType_sldd();
        end
    end

    if ModelUpdate
        if contains(swcTypes,'SWC_DID')
            cd(arch_path);
            FVT_SWC_DID_Autobuild(); 
        end
    else
        % SWC_FDC_type Autobuild
        cd(projectPath)
        FVT_SWC_Autobuild()
    end

    Modify_APPType_sldd()
end


evalin('base', 'run vcu_local_hdr');
evalin('base', 'run MC');

% in arch_path (inp, outp, util)
cd(arch_path)
load_var_cal_buses

% in hal_path
cd([arch_path filesep 'hal'])
load_var_cal_buses
% 
% in inp_path
cd([arch_path filesep 'inp'])
load_var_cal_buses
% 
% % in app_path	(app/*)
cd([arch_path filesep 'app'])
load_var_cal_buses
cd(arch_path)

model = 'SWC_ETE_type';
open_system(model)
Simulink.importExternalCTypes(model,'Names',{'cfloat32'});
Simulink.importExternalCTypes(model,'Names',{'EvAdc_SignalDataType_Fake','System_Adc_Signal_Fake','float32'});

if code_generate
    %% Build models
    cd(arch_path)
    buildmodel('SWC_APP_type', arch_path)
    buildmodel('SWC_ETE_type', arch_path)
    
    cd(project_path)
    copyfile([project_path '/documents/FVT_API/FVTMC_API.h'],[arch_path '/SWC_ETE_type_autosar_rtw'])

    %% Copy files to fvt_app_path
    Clone_path = extractBefore(project_path,'\mcu-gen1');
    last_slash_index = find(project_path == '\', 1, 'last');
    car_model_folder = project_path(last_slash_index+1:end);
    RAW_CODE_folder = ['RAW_CODE_' car_model_folder];
    mkdir(Clone_path, RAW_CODE_folder);
    RAW_CODE_path = [Clone_path '\' RAW_CODE_folder];
    [~, Car_Model] = fileparts(project_path);

    ETE_code_path = CopyFilestofvt_app_path('SWC_ETE_type_autosar_rtw', arch_path, RAW_CODE_path);
    APP_code_path = CopyFilestofvt_app_path('SWC_APP_type_autosar_rtw', arch_path, RAW_CODE_path);

    slprj_path    = [arch_path '\slprj\autosar\_sharedutils'];
    %fvt_app_path  = [Clone_path '\fdc-bsp-m7-autosar\source\fvt_app\' Car_Model];
    %document_path = [project_path '\documents'];
    
    mkdir(RAW_CODE_path,'_sharedutils');

    % Create Merged_a2l folder
    if exist([RAW_CODE_path '\Merged_a2l'], 'dir') ~= 7
        mkdir(RAW_CODE_path, 'Merged_a2l');
    end
    
    % a2l
    files = dir([ETE_code_path '\*.a2l']);
    for i = 1:length(files)
        copyfile([files(i).folder '\' files(i).name],[RAW_CODE_path '\\' files(i).name])
    end

    files = dir([APP_code_path '\*.a2l']);
    for i = 1:length(files)
        copyfile([files(i).folder '\' files(i).name],[RAW_CODE_path '\\' files(i).name])
    end

    % a2l merge and rework
    Gen_A2L()

    % sharedutils
    files = dir([slprj_path '\**\*.c']);
    for i = 1:length(files)
        copyfile([files(i).folder '\' files(i).name],[RAW_CODE_path '\_sharedutils\' files(i).name])
    end
    files = dir([slprj_path '\**\*.h']);
    for i = 1:length(files)
        copyfile([files(i).folder '\' files(i).name],[RAW_CODE_path '\_sharedutils\' files(i).name])
    end

end
%% END of main

%% run xxx_var.m, xxx_cal.m and BXXX_outputs.m
function load_var_cal_buses

    names = dir;

    for i = 1:length(names)

        if names(i).isdir == 0; continue; end
        if ~isempty(strfind(names(i).name, '.')); continue; end
        if ~isempty(strfind(names(i).name, 'Test')); continue; end
        if ~isempty(strfind(names(i).name, 'test')); continue; end
        if ~isempty(strfind(names(i).name, 'MINT')); continue; end
        if ~isempty(strfind(names(i).name, 'slprj')); continue; end
        if ~isempty(strfind(names(i).name, 'sfprj')); continue; end
        if ~isempty(strfind(names(i).name, '_grt_rtw')); continue; end
        if ~isempty(strfind(names(i).name, '_ert_rtw')); continue; end
        if ~isempty(strfind(names(i).name, '_dev')); continue; end
        if ~isempty(strfind(names(i).name, '+PccuCALFLASH')); continue; end

        % % Set path % %
        pathname = [pwd filesep names(i).name];
        addpath(pathname);

        % % Run Calibration % %

        var_name = [names(i).name '_var'];

        if 2 == exist(var_name, 'file')
            evalin('base', ['run ' var_name]);
        end

        cal_name = [names(i).name '_cal'];

        if 2 == exist(cal_name, 'file')
            evalin('base', ['run ' cal_name]);
        end

        % % Run Bus defination % %

        bus_name = ['B' upper(names(i).name) '_outputs'];

        if 1 == evalin('base', ['exist(''' bus_name ''' , ''var'')'])
            evalin('base', ['clear ' bus_name]);
        end

        if 2 == exist(bus_name, 'file')
            evalin('base', ['run ' bus_name]);
        end

        % % Run Array declaration % %

        array_name = [names(i).name '_array'];

        if 2 == exist(array_name, 'file')
            evalin('base', ['run ' array_name]);
        end

    end

end

function ModelConfig(model)
    cs = getActiveConfigSet(model);
    set_param(cs, 'GenerateASAP2', 'on');
    % set_param(cs, 'TargetLongLongMode','on');
    set_param(cs, 'SuppressUnreachableDefaultCases', 'off');
    set_param(cs, 'ConvertIfToSwitch', 'off');
    set_param(cs, 'BooleanTrueId', 'true_MatlabRTW');
    set_param(cs, 'BooleanFalseId', 'false_MatlabRTW');
    set_param(cs, 'DataTypeReplacement', 'CoderTypedefs');
    set_param(cs, 'ProdHWDeviceType', 'ARM Compatible->ARM Cortex-M'); % Production device vendor and type
    set_param(cs, 'ProdLongLongMode', 'on'); % Support long long
    set_param(cs, 'ProdEqTarget', 'on'); % Test hardware is the same as production hardware
    set_param(cs, 'PortableWordSizes', 'on'); % Enable portable word sizes
    set_param(cs, 'UtilityFuncGeneration','Shared location');
    set_param(cs, 'GenerateSharedConstants','off');
end

function buildmodel(model, arch_path)
    open_system(model)
    ModelConfig(model)
    slbuild(model)
    save_system(model)
    close_system(model)
    cd(arch_path)
end

function code_path = CopyFilestofvt_app_path(SWC_trw, arch_path, RAW_CODE_path)
    code_path = [arch_path '\' SWC_trw];
    mkdir(RAW_CODE_path, SWC_trw);

    files = dir([code_path '\*.c']);
    for i = 1:length(files)
        copyfile([files(i).folder '\' files(i).name],[RAW_CODE_path '\' SWC_trw '\' files(i).name])
    end

    files = dir([code_path '\*.h']);
    for i = 1:length(files)
        copyfile([files(i).folder '\' files(i).name],[RAW_CODE_path '\' SWC_trw '\' files(i).name])
    end
end

end

function Modify_APPType_sldd()
% Remove Bxxx_outputs in APPType.sldd
dictObj = Simulink.data.dictionary.open('APPTypes.sldd');
hDesignData = dictObj.getSection('Global');
childNamesList = hDesignData.evalin('who');
for n = 1:numel(childNamesList)
    if strcmp(childNamesList{n},'AppModeRequestType')
        continue
    elseif startsWith(childNamesList{n},'B') && endsWith(childNamesList{n},'_outputs') && ~strcmp(childNamesList{n},'BOUTP2_outputs')
        deleteEntry(hDesignData, [childNamesList{n}]);
    end
end
saveChanges(dictObj);
Simulink.data.dictionary.closeAll;
end
   
function cleanupSldd()
dictObj = Simulink.data.dictionary.open('APPTypes.sldd');
saveChanges(dictObj);
close(dictObj);
end