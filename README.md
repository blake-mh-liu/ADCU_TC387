# TC387QP AUTOSAR BSP for Motor Control Unit (MCU)
This repository contains EB tresos project files, arxml files and source codes for Motor Control Unit (MCU) TC387QP cores, which follows AUTOSAR.

## Support boards
- MCU hardware revision XA

## Prerequisites
- EB tresos studio 8.8.11 TC387QP Devdrop, [EB Tresos installation tutorial here](https://foxtronev.atlassian.net/wiki/spaces/FDC/pages/53543203/Install+EB+tresos+studio) (You'd only need to install EB Tresos if you're working on configuring the ACG. No installation is required if your purpose is solely to build code.)
- TASKING_TriCore-VX_v6.3r1, [TASKING installation tutorial here](https://foxtronev.atlassian.net/wiki/spaces/FDC/pages/667910313/Tasking+compiler) (Not required if you're building code in the docker container.)
- [Docker](https://docs.docker.com/engine/install/) (Not required if you're building code on Windows.)
- WSL and Docker Desktop, [WSL and Docker Desktop installation tutorial here](https://foxtronev.atlassian.net/wiki/spaces/FDC/pages/281444400/Install+WSL+and+Docker+Desktop), then you can build code based on **Linux**.
- [Set up the ceedling unit testing framework for local build testing](#ceedling-setup).

## Download & Gen code
1. Use Git to download project: `git clone git@github.com:foxtron-ev/mcu-gen1.git`
2. Go to *mcu-gen1 folder*, check whether *output* folder exists, if yes, delete the *output* folder.
3. Launch EB tresos and [import project](https://foxtronev.atlassian.net/wiki/spaces/FDC/pages/53543214/Import+project) from one of the projects in the `workspace` directory.
4. Run [generate code](https://foxtronev.atlassian.net/wiki/spaces/FDC/pages/102400001/Generate+code+from+Imported+project+For+ACP8.8.7+with+GHS+complier)

NOTE: Since PR228 we have removed the "SystemModel2.tdb" from version control, you may see the errors in "Problem view" at beginning, the error will gone after you executed the "MultiTask" because the "SystemModel2.tdb" will be re-created.

## Build project

### Windows

1. Open file *"mcu-gen1\util\launch_cfg.bat"*
    1. Find below sentence, then check whether *TASKING compiler* path is the same as yours, configure it if different:

    ```
    IF [%TOOLPATH_COMPILER%]==[] SET TOOLPATH_COMPILER=C:\TASKING\TriCore_v6.3r1\ctc
    ```

2. Open a CMD window and change directory to *mcu-gen1\util*, then enter command `launch.bat` to prepare compile environment.
**NOTE:** DO NOT CLOSE the CMD window until you finish your compile task.
3. In CMD window, enter command `make -j` to build.

### Linux


## Coding Style


## Contribution Guide


## Bootinfo parameters


## Project structure
```    	    
└── 📁source
    └── # Our own source code.
    └── 📁fvt_app
        └── 📁SWC_APP_type_autosar_rtw
            └── # SWC_APP
        └── 📁SWC_CDD_type_autosar_rtw
            └── # SWC_CDD          			
    └── 📁fvt_cdd
        └── 📁common
            └── # common cdd code shared by mcu gen1
└── 📁tresos
    └── # The minimal Tresos Studio for code generation.
└── 📁util
    └── # Build tools and utilities.        		
```


## CAN Bus Topology

### For hardware generation 1


### For hardware generation 2


### For Model U (hardware generation 2)


## Supported Car Models

