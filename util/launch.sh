#!/bin/bash

source launch_cfg.sh
if [[ -z "$*" ]]; then
  make show_rules
  bash
else
  x=$*; x="${x/make /make SHELL=\${USERBUILD_SHELL} EB_VERBOSE=${EB_VERBOSE}}"
  [[ -n ${EB_VERBOSE} ]] || echo -e "\n\n\n${PWD}/launch.sh: invoking $x\n\n\n"
  $x
fi

