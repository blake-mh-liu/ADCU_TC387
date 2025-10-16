#!/bin/sh

# welcome
echo "    ____        _ _ _   ___           _____         "
echo "   / ___| _ __ | (_) |_|_ _|_ __ ___ | ____|_  __   "
echo "   \___ \| '_ \| | | __|| || '_ \` _ \|  _| \ \/ /   "
echo "    ___) | |_) | | | |_ | || | | | | | |___ >  <    "
echo "   |____/| .__/|_|_|\__|___|_| |_| |_|_____/_/\_\   "
echo "   |  _ \|_|__ ___  _ __   ___ _ __| |_(_) ___  ___ "
echo "   | |_) | '__/ _ \| '_ \ / _ \ '__| __| |/ _ \/ __|"
echo "   |  __/| | | (_) | |_) |  __/ |  | |_| |  __/\__ \ "
echo "   |_|___|_|  \___/| .__/_\___|_|   \__|_|\___||___/"
echo "    / ___|_ __ ___ |_| _| |_ ___  _ __              "
echo "   | |   | '__/ _ \/ _\` | __/ _ \| '__|             "
echo "   | |___| | |  __/ (_| | || (_) | |                "
echo "    \____|_|  \___|\__,_|\__\___/|_|                "
echo "                                          anse1271   "
echo ""
echo ""

# prepare workspace
FILE_PREF_GENERAL=pref_general.xdm
FILE=sample.properties
FILE_TMP=$FILE.tmp

# alternatively, file name of pref_generl can be passed as paramter
if [ "$1" ]; then
  echo "Value of pref_general file was given as parameter: $1"
  FILE_PREF_GENERAL="$1"
fi

# check if pref_general.xdm is available
if test -f "$FILE_PREF_GENERAL"; then
  # remove existing file
  if test -f "$FILE"; then
      echo "Removed $FILE file."
      rm -f sample.properties;
  fi

  echo "Start creating new $FILE file."
  
  # using PCRE (Perl Compatible Regular Expressions) via grep:-oP (o= only matches; P= Perl) to filter pref_general.xdm 
  cat $FILE_PREF_GENERAL | grep -oP '(?:<d:ctr (name)=\"([\w\d]*)\"\>|(name)=\"(ModuleId)\" (value)=\"([\w\d]*)\"|(name)=\"(PreConfig)\" (value)=\"([\w\d]*)\"|(name)=\"(RecConfig)\" (value)=\"([\w\d]*)\")' > $FILE_TMP

  # regex filter for module scope
  re_scope="<d:ctr name=\"([_a-zA-Z0-9-]*)\">"
  # regex filter for ModuleType
  re_Type="name=\"ModuleId\" value=\"([_a-zA-Z0-9-]*)_TS_([_a-zA-Z0-9-]*)\""
  # regex filter for RecConfig
  re_Rec="name=\"RecConfig\" value=\"([a-zA-Z0-9-]*)\""
  # regex filter for PreConfig
  re_Pre="name=\"PreConfig\" value=\"([a-zA-Z0-9-]*)\""

  line="";
  module_info=("" "" "")  # (ModuleType, PreConfig, RecConfig)
  while read p; do

    # if line is about scope
    if [[ $p =~ $re_scope ]]; then
      # stored values available?
      if [ -n "${module_info[0]}" ];then
        # create line
        line=$line${module_info[0]}
        if [ -n "${module_info[1]}" ];then
          line=$line", "${module_info[1]}
        fi;
        if [ -n "${module_info[2]}" ];then
          line=$line", "${module_info[2]}
        fi;
        # write line to file
        echo $line >> $FILE;
      fi;
      
      # reset line and array
      line=""
      module_info[0]=""
      module_info[1]=""
      module_info[2]=""
    fi;
    
    # if line is about type
    if [[ $p =~ $re_Type ]]; then
      # add module type info to line
      module_info[0]="Module.${BASH_REMATCH[1]}: id=${BASH_REMATCH[1]}_TS_${BASH_REMATCH[2]}"
    fi
  
    # if line is about preconfig
    if [[ $p =~ $re_Pre ]]; then
      # add preconfig info to line
      module_info[1]="preConfig=${BASH_REMATCH[1]}"
    fi
  
    # if line is about recommended config
    if [[ $p =~ $re_Rec ]]; then
     # add recommended config info to line
      module_info[2]="recConfig=${BASH_REMATCH[1]}"
    fi
  
  done <$FILE_TMP

  # write last line to file since we quit the loop already
  echo $line >> $FILE;
  
  # sort properties file
   sort $FILE -o $FILE
   
  # add ProjectTemplateUrl
  echo "ProjectTemplateUrl: " >> $FILE;
  
  # SysDImporter (assume name of Importer stays the same as in Lead reference)
  echo "SysDImporter: SystemExtract_SystemModel" >> $FILE;
  
  # EcuInstances
  search_result=$(cat $FILE_PREF_GENERAL | grep -oP '(?:(name)=\"EcuInstance\" (value)=\"([\w\d\/]*/ECUINSTANCES/[\w\d\/]*)\")')
  # regex filter for EcuInstance
  re_Ecu="([-a-zA-Z0-9\/]*/ECUINSTANCES/[-a-zA-Z0-9\/]*)"
  if [[ $search_result =~ $re_Ecu ]]; then
    echo "EcuInstance: "${BASH_REMATCH[0]} >> $FILE;
  fi
  
  # cleanup
  rm -f $FILE_TMP
  
  if test -f "$FILE"; then
    echo "Script was successfully executed. Quit programm."
  fi
else # pref_general.xdm was not found
  echo "$FILE_PREF_GENERAL was not found. Quit program."
fi # end pref_general.xdm check
#end