# --------{ EB Automotive Makefile }--------

#################################################################
# DEFINITIONS

ifeq ($(BUILD_MODE),LIB)
ifeq ($(MODULE),Cry)
LIB_VARIANTS += Cry_BASE
endif
endif

Cry_CORE_PATH           ?= $(PLUGINS_BASE)\Cry_$(Cry_VARIANT)
Cry_OUTPUT_PATH         ?= $(AUTOSAR_BASE_OUTPUT_PATH)

Cry_GEN_FILES           :=                                          \
  $(Cry_CORE_PATH)\generate\include\Cry_SSGStateConfig.h            \
  $(Cry_CORE_PATH)\generate\include\Cry_SSGSeedConfig.h             \
  $(Cry_CORE_PATH)\generate\include\Cry_SSGGenerateConfig.h         \
  $(Cry_CORE_PATH)\generate\include\Cry_SHA3Config.h                \
  $(Cry_CORE_PATH)\generate\include\Cry_SHA2Config.h                \
  $(Cry_CORE_PATH)\generate\include\Cry_SHA1Config.h                \
  $(Cry_CORE_PATH)\generate\include\Cry_SHA_CommonConfig.h          \
  $(Cry_CORE_PATH)\generate\include\Cry_RsaSsaV15VerifyConfig.h     \
  $(Cry_CORE_PATH)\generate\include\Cry_RsaSsaV15VerifyCbk.h        \
  $(Cry_CORE_PATH)\generate\include\Cry_RsaSsaV15GenConfig.h        \
  $(Cry_CORE_PATH)\generate\include\Cry_RsaSsaPssVerifyConfig.h     \
  $(Cry_CORE_PATH)\generate\include\Cry_RsaSsaPssVerifyCbk.h        \
  $(Cry_CORE_PATH)\generate\include\Cry_MD5Config.h                 \
  $(Cry_CORE_PATH)\generate\include\Cry_KEY_SYM_ExtractConfig.h     \
  $(Cry_CORE_PATH)\generate\include\Cry_HMACVrfyConfig.h            \
  $(Cry_CORE_PATH)\generate\include\Cry_HMACGenConfig.h             \
  $(Cry_CORE_PATH)\generate\include\Cry_HMACConfig.h                \
  $(Cry_CORE_PATH)\generate\include\Cry_ExtractRsaPublicKeyConfig.h \
  $(Cry_CORE_PATH)\generate\include\Cry_ExtractECPubKeyConfig.h     \
  $(Cry_CORE_PATH)\generate\include\Cry_EdDSAVrfyConfig.h           \
  $(Cry_CORE_PATH)\generate\include\Cry_EdDSAGenConfig.h            \
  $(Cry_CORE_PATH)\generate\include\Cry_EdDSAConfig.h               \
  $(Cry_CORE_PATH)\generate\include\Cry_CVCPublicKeyExtractConfig.h \
  $(Cry_CORE_PATH)\generate\include\Cry_CRC_Config.h                \
  $(Cry_CORE_PATH)\generate\include\Cry_CommonConfig.h              \
  $(Cry_CORE_PATH)\generate\include\Cry_CMACVrfyConfig.h            \
  $(Cry_CORE_PATH)\generate\include\Cry_CMACGenConfig.h             \
  $(Cry_CORE_PATH)\generate\include\Cry_CcmEncryptConfig.h          \
  $(Cry_CORE_PATH)\generate\include\Cry_CcmDecryptConfig.h          \
  $(Cry_CORE_PATH)\generate\include\Cry_CCM_CommonConfig.h          \
  $(Cry_CORE_PATH)\generate\include\Cry_CbcPkcs7EncryptConfig.h     \
  $(Cry_CORE_PATH)\generate\include\Cry_CbcPkcs7DecryptConfig.h     \
  $(Cry_CORE_PATH)\generate\include\Cry_AES_EncryptConfig.h         \
  $(Cry_CORE_PATH)\generate\include\Cry_AES_DecryptConfig.h         \
  $(Cry_CORE_PATH)\generate\include\Cry_AES_CommonConfig.h

Cry_lib_LIB_OUTPUT_PATH := $(Cry_CORE_PATH)\lib

#################################################################
# REGISTRY

Cry_DEPENDENT_PLUGINS := base_make tresos
Cry_VERSION           := 2.00.00
Cry_DESCRIPTION       := Cry Basic Software Makefile PlugIn for Autosar

CC_INCLUDE_PATH       += \
  $(Cry_CORE_PATH)\include \
  $(Cry_CORE_PATH)\lib_include \
  $(Cry_OUTPUT_PATH)\include

ASM_INCLUDE_PATH      +=
CPP_INCLUDE_PATH      +=
