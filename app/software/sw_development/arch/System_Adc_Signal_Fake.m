classdef System_Adc_Signal_Fake < Simulink.IntEnumType
    % MATLAB enumeration class definition generated from template
    
    enumeration
        PMIC_5V8_SIGNAL(0),
		KL15_SIGNAL(1),
		KL30_SIGNAL(2),
		HV_LV_13V5_SIGNAL(3),
		QUC_1V25_SIGNAL(4),
		QUC_3V3_SIGNAL(5),
		QUC_5V0_SIGNAL(6),
		QVR_5V0_SIGNAL(7),
		QT1_5V0_SIGNAL(8),
		QT2_SIGNAL(9),
		QCO_5V0_SIGNAL(10),
		BOOST_LDO_12V0_SIGNAL(11),
		BOOST_21V5_SIGNAL(12),
		HV_U_SIGNAL(13),
		HV_V_SIGNAL(14),
		CURRENT_U_IO_SIGNAL(15),
		CURRENT_V_IO_SIGNAL(16),
		CURRENT_W_IO_SIGNAL(17),
		SIN_P_SIGNAL(18),
		SIN_N_SIGNAL(19),
		COS_P_SIGNAL(20),
		COS_N_SIGNAL(21),
		EXC_P_SIGNAL(22),
		EXC_N_SIGNAL(23),
		TEMP_MCU_SIGNAL(24),
		TEMP_FLYBACK_SIGNAL(25),
		TEMP_OIL_SIGNAL(26),
		TEMP_M_U_SIGNAL(27),
		TEMP_M_V_SIGNAL(28),
		TEMP_M_W_SIGNAL(29),
		TEMP_SIC_U_SIGNAL(30),
		TEMP_SIC_V_SIGNAL(31),
		TEMP_SIC_W_SIGNAL(32),
		SYSTEM_ADC_SIGNAL_COUNT(33)
    end

    methods (Static)
        
        function defaultValue = getDefaultValue()
            % GETDEFAULTVALUE  Returns the default enumerated value.
            %   If this method is not defined, the first enumeration is used.
            defaultValue = System_Adc_Signal_Fake.PMIC_5V8_SIGNAL;
        end

        function dScope = getDataScope()
            % GETDATASCOPE  Specifies whether the data type definition should be imported from,
            %               or exported to, a header file during code generation.
            dScope = 'Imported';
        end

        function desc = getDescription()
            % GETDESCRIPTION  Returns a description of the enumeration.
            desc = '';
        end
        
        function headerFile = getHeaderFile()
            % GETHEADERFILE  Specifies the name of a header file. 
            headerFile = 'FVTMC_API.h';
        end
        
        function flag = addClassNameToEnumNames()
            % ADDCLASSNAMETOENUMNAMES  Indicate whether code generator applies the class name as a prefix
            %                          to the enumeration.
            flag = false;
        end

    end

end
