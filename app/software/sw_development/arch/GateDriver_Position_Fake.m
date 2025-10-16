classdef GateDriver_Position_Fake < Simulink.IntEnumType
    % MATLAB enumeration class definition generated from template
    
    enumeration
        GateDriverPos_uHS(0),
		GateDriverPos_uLS(1),
		GateDriverPos_vHS(2),
		GateDriverPos_vLS(3),
		GateDriverPos_wHS(4),
		GateDriverPos_wLS(5),
		GateDriverPos_Count(6)
    end

    methods (Static)
        
        function defaultValue = getDefaultValue()
            % GETDEFAULTVALUE  Returns the default enumerated value.
            %   If this method is not defined, the first enumeration is used.
            defaultValue = GateDriver_Position_Fake.GateDriverPos_uHS;
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
