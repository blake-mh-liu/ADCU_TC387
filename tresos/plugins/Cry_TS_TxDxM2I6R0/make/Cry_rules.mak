# --------{ EB Automotive Makefile }--------

#################################################################
# DEFINITIONS


#################################################################
# REGISTRY

Cry_lib_FILES      :=

Cry_src_FILES      +=                                    \
  $(Cry_CORE_PATH)\src\Cry_SSGSeed.c                     \
  $(Cry_CORE_PATH)\src\Cry_SSGGenerate.c                 \
  $(Cry_CORE_PATH)\src\Cry_SHA3_Impl.c                   \
  $(Cry_CORE_PATH)\src\Cry_SHA3.c                        \
  $(Cry_CORE_PATH)\src\Cry_SHA2.c                        \
  $(Cry_CORE_PATH)\src\Cry_SHA1.c                        \
  $(Cry_CORE_PATH)\src\Cry_SHA_Common.c                  \
  $(Cry_CORE_PATH)\src\Cry_RsaSsaV15Verify.c             \
  $(Cry_CORE_PATH)\src\Cry_RsaSsaV15Gen.c                \
  $(Cry_CORE_PATH)\src\Cry_RsaSsaPssVerify.c             \
  $(Cry_CORE_PATH)\src\Cry_MD5.c                         \
  $(Cry_CORE_PATH)\src\Cry_LN.c                          \
  $(Cry_CORE_PATH)\src\Cry_KEY_SYM_Extract.c             \
  $(Cry_CORE_PATH)\src\Cry_HMACVrfy.c                    \
  $(Cry_CORE_PATH)\src\Cry_HMACGen.c                     \
  $(Cry_CORE_PATH)\src\Cry_ExtractRSAPublicKey.c         \
  $(Cry_CORE_PATH)\src\Cry_ExtractECPubKey.c             \
  $(Cry_CORE_PATH)\src\Cry_EdDSAVrfy.c                   \
  $(Cry_CORE_PATH)\src\Cry_EdDSAGen.c                    \
  $(Cry_CORE_PATH)\src\Cry_EdDSA.c                       \
  $(Cry_CORE_PATH)\src\Cry_DerCVC.c                      \
  $(Cry_CORE_PATH)\src\Cry_Der.c                         \
  $(Cry_CORE_PATH)\src\Cry_CVCPublicKeyExtract.c         \
  $(Cry_CORE_PATH)\src\Cry_CRC.c                         \
  $(Cry_CORE_PATH)\src\Cry_Common.c                      \
  $(Cry_CORE_PATH)\src\Cry_CMACVrfy.c                    \
  $(Cry_CORE_PATH)\src\Cry_CMACGen.c                     \
  $(Cry_CORE_PATH)\src\Cry_CMAC.c                        \
  $(Cry_CORE_PATH)\src\Cry_CCMEncrypt.c                  \
  $(Cry_CORE_PATH)\src\Cry_CCMDecrypt.c                  \
  $(Cry_CORE_PATH)\src\Cry_CCM_Common.c                  \
  $(Cry_CORE_PATH)\src\Cry_CbcPkcs7Encrypt.c             \
  $(Cry_CORE_PATH)\src\Cry_CbcPkcs7Decrypt.c             \
  $(Cry_CORE_PATH)\src\Cry_Base64.c                      \
  $(Cry_CORE_PATH)\src\Cry_AES_Encrypt.c                 \
  $(Cry_CORE_PATH)\src\Cry_AES_Decrypt.c                 \
  $(Cry_CORE_PATH)\src\Cry_AES_Common.c                  \
  $(Cry_OUTPUT_PATH)\src\Cry_SSGStateConfig.c            \
  $(Cry_OUTPUT_PATH)\src\Cry_SSGSeedConfig.c             \
  $(Cry_OUTPUT_PATH)\src\Cry_SSGGenerateConfig.c         \
  $(Cry_OUTPUT_PATH)\src\Cry_SHA3Config.c                \
  $(Cry_OUTPUT_PATH)\src\Cry_SHA2Config.c                \
  $(Cry_OUTPUT_PATH)\src\Cry_SHA1Config.c                \
  $(Cry_OUTPUT_PATH)\src\Cry_RsaSsaV15VerifyConfig.c     \
  $(Cry_OUTPUT_PATH)\src\Cry_RsaSsaV15GenConfig.c        \
  $(Cry_OUTPUT_PATH)\src\Cry_RsaSsaPssVerifyConfig.c     \
  $(Cry_OUTPUT_PATH)\src\Cry_MD5Config.c                 \
  $(Cry_OUTPUT_PATH)\src\Cry_KEY_SYM_ExtractConfig.c     \
  $(Cry_OUTPUT_PATH)\src\Cry_HMACVrfyConfig.c            \
  $(Cry_OUTPUT_PATH)\src\Cry_HMACGenConfig.c             \
  $(Cry_OUTPUT_PATH)\src\Cry_ExtractRsaPublicKeyConfig.c \
  $(Cry_OUTPUT_PATH)\src\Cry_ExtractECPubKeyConfig.c     \
  $(Cry_OUTPUT_PATH)\src\Cry_EdDSAVrfyConfig.c           \
  $(Cry_OUTPUT_PATH)\src\Cry_EdDSAGenConfig.c            \
  $(Cry_OUTPUT_PATH)\src\Cry_CVCPublicKeyExtractConfig.c \
  $(Cry_OUTPUT_PATH)\src\Cry_CRC_Config.c                \
  $(Cry_OUTPUT_PATH)\src\Cry_CMACVrfyConfig.c            \
  $(Cry_OUTPUT_PATH)\src\Cry_CMACGenConfig.c             \
  $(Cry_OUTPUT_PATH)\src\Cry_CcmEncryptConfig.c          \
  $(Cry_OUTPUT_PATH)\src\Cry_CcmDecryptConfig.c          \
  $(Cry_OUTPUT_PATH)\src\Cry_CbcPkcs7EncryptConfig.c     \
  $(Cry_OUTPUT_PATH)\src\Cry_CbcPkcs7DecryptConfig.c     \
  $(Cry_OUTPUT_PATH)\src\Cry_CbcPkcs7DecryptConfig.c     \
  $(Cry_OUTPUT_PATH)\src\Cry_AES_EncryptConfig.c         \
  $(Cry_OUTPUT_PATH)\src\Cry_AES_DecryptConfig.c

LIBRARIES_TO_BUILD     += Cry_src

DIRECTORIES_TO_CREATE += $(Cry_lib_LIB_OUTPUT_PATH)

CC_FILES_TO_BUILD       +=
CPP_FILES_TO_BUILD      +=
ASM_FILES_TO_BUILD      +=

MAKE_CLEAN_RULES        +=
MAKE_GENERATE_RULES     +=
MAKE_COMPILE_RULES      +=
#MAKE_DEBUG_RULES       +=
MAKE_CONFIG_RULES       +=
#MAKE_ADD_RULES         +=

define defineCryLibOutputPATH
$(1)_OBJ_OUTPUT_PATH    := $(Cry_lib_LIB_OUTPUT_PATH)
endef
$(foreach SRC,$(basename $(notdir $(subst \,/,$(Cry_lib_FILES)))),\
$(eval $(call defineCryLibOutputPATH,$(SRC))))

#################################################################
# DEPENDENCIES (only for assembler files)
#

#################################################################
# RULES
