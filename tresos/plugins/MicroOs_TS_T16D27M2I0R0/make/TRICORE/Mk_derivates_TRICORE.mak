# Derivative mapping for TRICORE CPUs.
#
# If MK_CPU is not defined explicitly the CPU will have the same external and internal name.

ifeq ($(DERIVATE),TC21XL)
MK_CPU := TC22XL
endif
