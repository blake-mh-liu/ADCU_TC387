function BEOP_outputs(varargin)
%===========$Update Time :  2025-09-11 12:53:03 $=========
disp('Loading $Id: BEOP_outputs.m  2025-09-11 12:53:03    foxtron $ FVT_export_businfo_v2.0 2021-11-02')
%===========$Update Time :  2025-09-11 12:53:03 $=========
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
    'BEOP_outputs',...
       '', ...
       sprintf(''), { ... 
         {'VEOP_bMotEnaReq_flg'  ,1,  'boolean'  ,-1, 'real' ,'Sample'};...
         {'VEOP_nEOPSpdReq_rpm'  ,1,  'single'  ,-1, 'real' ,'Sample'};...
      } ... 
    } ...
  }'; 
if ~suppressObject
    % Create bus objects in the MATLAB base workspace
    Simulink.Bus.cellToObject(cellInfo)
end
end
