################################################################################
# Tresos.mk
################################################################################
TRESOS_BIN_PATH?=$(TRESOS_ROOT)/bin
TRESOS_CMD=$(TRESOS_BIN_PATH)/tresos_cmd.bat
SUITE_CFG_DIR?=$(SUITE_ROOT)/$(SUITE_NAME)/Cfg
TRESOS_OUT_DIR?=$(SUITE_ROOT)/CfgMcal
TRESOS_XDM_FILES=$(TRESOS_WORKSPACE)/$(TRESOS_PROJECT_NAME)/config/*.xdm
TRESOS_EPC_FILES=$(SUITE_CFG_DIR)/$(SUITE_CFG)

ifeq ($(BUILDENV),DEMOAPP)
BUILD_BASE_PATH=.
DEMOAPP_CONFIG_PATH=1_ToolEnv/2_Tresos/AS440/DemoApp/config
TRESOS_ROOT?=C:/sofit/aurix2g_sw_mcal/tresos/26.2.0/tresos/tresos
TRESOS_PROJECT_NAME?=DemoApp
TRESOS_BIN_PATH?=$(TRESOS_ROOT)/bin

TRESOS_GEN_BAT=$(TRESOS_BIN_PATH)/tresos_cmd.bat
TRESOS_WORKSPACE=1_ToolEnv/2_Tresos/AS440
TRESOS_OUT_DIR=0_Src/AppSw/Tricore/CfgMcal

TRESOS_GEN_COMMAND=$(TRESOS_GEN_BAT) -data $(TRESOS_WORKSPACE) generate -o $(TRESOS_OUT_DIR) $(TRESOS_PROJECT_NAME)
endif

EPC_QUALIFIED_NAME?=$(SUITE_CFG)

TRESOS_ARG_XDM=-data $(TRESOS_WORKSPACE) generate -o $(TRESOS_OUT_DIR) $(TRESOS_PROJECT_NAME)
TRESOS_ARG_EPC=-Dtarget=$(DEVICE) -Dderivate=$(DERIVATE) legacy generate $(EPC_QUALIFIED_NAME) -c $(SUITE_CFG_DIR) -o $(TRESOS_OUT_DIR)

#TRESOS_OUT_DIR:=$(subst \,/,$(realpath $(TRESOS_OUT_DIR)))
#TRESOS_OUT_DIR:=$(subst /c/,c:/,$(TRESOS_OUT_DIR))

.phony: demoapp_build appcfg clean out_clean
demoapp_build: clean out_clean
	@$(TRESOS_GEN_COMMAND)

appcfg: $(TRESOS_OUT_DIR)/status.txt

.ONESHELL:
# Generate source files by Tresos configuration

TRESOS_PLUGIN_LINK=$(subst \,/,$(TRESOS_ROOT)/links)

$(TRESOS_OUT_DIR)/status.txt:
	@echo $(SRC_FOLDERS)
	@echo Generating Tresos Configurations ...
	@if [[ ! -d "$(@D)" ]]; then	 					\
		echo Creating $(@D);							\
		mkdir -p $(@D);									\
	fi	
	@-rm -rf $(@D)/*.*
	
	@if [[ ! -d "$(TRESOS_PLUGIN_LINK)" ]]; then	 	\
		echo Creating $(TRESOS_PLUGIN_LINK);			\
		mkdir $(TRESOS_PLUGIN_LINK);					\
	fi	
	@-rm -f $(TRESOS_PLUGIN_LINK)/*.link
	
	@python $(ASE_LIB)/TresosLib.py  "$(SRC_FOLDERS)"  "$(TRESOS_ROOT)" "PluginsTresos"
	
ifeq ($(TRESOS_CFG_MODE),XDM)
	@$(TRESOS_CMD) $(subst /,//,$(TRESOS_ARG_XDM))
else
	@echo ... from EPC.
	@$(TRESOS_CMD) $(subst /,//,$(TRESOS_ARG_EPC))
endif
	@echo Tresos Generated the Configurations! > $(TRESOS_OUT_DIR)/status.txt

# Remove Geenrated Folders 2_Out and 9_Make
out_clean:
	@-rm -rf 2_Out/Tricore_$(COMPILER)/*
	@-rm -rf 2_Out/Tricore_$(COMPILER)
	@-rm -rf 1_ToolEnv/0_Build/9_Make/*
	@-rm -rf 1_ToolEnv/0_Build/9_Make
# Remove generated files by Tresos and all plugin links
clean:
	@-rm -f $(TRESOS_PLUGIN_LINK)/*.link
	@-rm -f $(TRESOS_PLUGIN_LINK)
	@-rm -rf 0_Src/AppSw/Tricore/CfgMcal
	@-rm -rf 0_Src/AppSw/Tricore/CfgMcal_FR
