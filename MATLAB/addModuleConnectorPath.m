% Latest examples is located at https://github.com/xethru/XeThru-ModuleConnector-Examples.
% 
% Target:
% all examples
% 
% Introduction:
% This function add ModuleConnector lib addresses according to your operating system.
% 
% prerequisite:
% this script should be placed in ModuleConnector\matlab\examples folder,

function addModuleConnectorPath(optarg)

    addpath('../../matlab/');
    addpath('../../include/');
    
    if nargin == 1
        if strcmp(optarg,'win32')
            addpath('../../lib32/');
            return;
        end
    end
    if ispc
        addpath('../../lib64/');
    elseif ismac || islinux
        addpath('../../lib/');
    end

end