% display X4 chip settings of XeThru modules
% 
% Prerequisite:
% This example should be placed in ModuleConnector\matlab\examples
% folder.
%
% Input: device serial port like "COM8"
% 
% Target module: X4M2xx, X4M3xx, X4M0x
%
% Example:
% ModuleConnector.Library;
% mc = ModuleConnector.ModuleConnector(device_name,0);
% xep = mc.get_xep();
% disp_x4_settings(xep);

function disp_x4_settings(xep)
    % Check values (to confirm we have the values we want);:
    disp("");
    disp("********** Current X4 settings **********");
    disp("");
    disp(['iterations: ' , num2str(xep.x4driver_get_iterations())]);
    disp(['pulses_per_step: ' , num2str(xep.x4driver_get_pulsesperstep())]);
    disp(['dac_min: ' , num2str(xep.x4driver_get_dac_min())]);
    disp(['dac_max: ' , num2str(xep.x4driver_get_dac_max())]);
    disp(['prf_div: ' , num2str(xep.x4driver_get_prf_div())]);
    disp(['tx_power: ' , num2str(xep.x4driver_get_tx_power())]);
    disp(['tx_center_frequency: ' , num2str(xep.x4driver_get_tx_center_frequency())]);
    disp(['downconversion: ' , num2str(xep.x4driver_get_downconversion())]);
    disp(['Frame area offset: ' , num2str(xep.x4driver_get_frame_area_offset())]);
    [frame_start, frame_stop] = xep.x4driver_get_frame_area();
    disp(['Frame Area: ' , num2str(frame_start) , ' to ' , num2str(frame_stop)]);
    clear
end