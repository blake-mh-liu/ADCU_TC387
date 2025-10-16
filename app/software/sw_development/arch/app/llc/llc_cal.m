%===========$Update Time :  2025-09-11 12:53:10 $=========
disp('Loading $Id: llc_cal.m  2025-09-11 12:53:10    foxtron $      FVT_export_businfo_v2.0 2021-11-02')

a2l_cal('LLCM_tlvtrATemp_C',     60); 
a2l_cal('LLCM_tlvtrBTemp_C',     60); 
a2l_cal('LLCM_tlvtrCTemp_C',     60); 
a2l_cal('LLCM_volfcooltFlowMax_C',     10); 
a2l_cal('LLCM_volfcooltFlowMin_C',     10); 
a2l_cal('LLCM_volfcooltFlowRampUp_C',     10); 
a2l_cal('LLCM_volfcooltFlowRampDown_C',     10); 
a2l_cal('LLCM_bTcooltFlowTrig_C',     0); 
a2l_cal('LLCM_volfcooltFlowMor_C',     10); 
a2l_cal('ALLC_volCoolFlowWater_X_kW',     [1 2 3 4]);
a2l_cal('ALLC_volCoolFlowWater_Y_degC',     [-40 -20 0 20]);
a2l_cal('MLLC_volCoolFlowWater_Z_M',     [1 2 3 4;1 2 3 4;1 2 3 4;1 2 3 4]);
a2l_cal('ALLC_volCoolFlowOil_X_degC',     [-40 -20 0 20]);
a2l_cal('MLLC_volCoolFlowOil_Y_T',     [14 14 14 14]);
a2l_cal('ALLC_volfCooltFlow_X_degC',     [-40 -20 0 20]);
a2l_cal('MLLC_volfCooltFlow_Y_T',     [1 2 3 4]);
