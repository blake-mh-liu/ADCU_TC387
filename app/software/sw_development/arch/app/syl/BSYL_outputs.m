function BSYL_outputs(varargin)
%===========$Update Time :  2025-09-11 10:26:33 $=========
disp('Loading $Id: BSYL_outputs.m  2025-09-11 10:26:33    foxtron $ FVT_export_businfo_v2.0 2021-11-02')
%===========$Update Time :  2025-09-11 10:26:33 $=========
% BXXX_outputs returns a cell array containing bus object information
% Optional Input: 'false' will suppress a call to Simulink.Bus.cellToObject
% when the m-file is executed.
% The order of bus element attributes is as follows:
% ElementName, Dimensions, DataType, SampleTime, Complexity, SamplingMode

suppressObject = false;
if nargin == 1 && islogical(varargin{1}) && varargin{1} == false
suppressObject = true;
elseif nargin > 1
error('Invalid input argument(s) encountered');
end

cellInfo = { ... 
           {... 
    'BSYL_outputs',...
       '', ...
       sprintf(''), { ... 
         {'VSYL_tqTMTqMax_Nm'  ,1,  'single'  ,-1, 'real' ,'Sample'};...
         {'VSYL_tqTMTqMin_Nm'  ,1,  'single'  ,-1, 'real' ,'Sample'};...
      } ... 
    } ...
  }'; 
if ~suppressObject
    % Create bus objects in the MATLAB base workspace
    Simulink.Bus.cellToObject(cellInfo)
end
end
