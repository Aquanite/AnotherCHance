#pragma once

#include "chance/types/types.h"
#include <chance/vm/GlobalVM.h>
#include <string.h>


namespace CE
{
    struct alignas(0x8) VMObject
    {
        static TypeReference TI32;
        static TypeReference TI64;
        static TypeReference TINative;
        static TypeReference TPointer;
        static TypeReference TSingle;

        TypeReference TrueType;
        bool Managed;

        enum class VMObjectType : uint8_t {
            VMVoid,
            VMi32,
            VMi64,
            VMNative,
            VMMObject,
            VMPtr,
            VMFloat,
        } Type;

        union
        {
            VMi32       Integer;
            VMi64       LongInteger;
            VMNative    NativeInteger;
            VMPtr       MObject;
            VMPtr       Pointer;
            VMFloat     Single;
        };

        static void Initialize()
        {
            TI32     = GlobalVM::Get(GlobalVM::Get("System.I32"));
            TI64     = GlobalVM::Get(GlobalVM::Get("System.I64"));
            TINative = GlobalVM::Get(GlobalVM::Get("System.INative"));
            TPointer = GlobalVM::Get(GlobalVM::Get("System.Pointer"));
            TSingle  = GlobalVM::Get(GlobalVM::Get("System.Single"));
            CE_ASSERT(TI32      != TypeReference::Fail, "TI32 is null!");
            CE_ASSERT(TI64      != TypeReference::Fail, "TI64 is null!");
            CE_ASSERT(TINative  != TypeReference::Fail, "TINative is null!");
            CE_ASSERT(TPointer  != TypeReference::Fail, "TPointer is null!");
            CE_ASSERT(TSingle   != TypeReference::Fail, "TSingle is null!");
        }

        static VMObject NewI32(VMi32 num)
        {
            return VMObject {
                .TrueType = TI32,
                .Managed = false,
                .Type = VMObjectType::VMi32,
                .Integer = num
            };
        }

        static VMObject NewI64(VMi64 num)
        {
            return VMObject {
                .TrueType = TI64,
                .Managed = false,
                .Type = VMObjectType::VMi64,
                .LongInteger = num  
            };
        }

        static VMObject NewNative(VMNative num)
        {
            return VMObject {
                .TrueType = TINative,
                .Managed = false,
                .Type = VMObjectType::VMNative,
                .NativeInteger = num  
            };
        }

        static VMObject NewObject(VMPtr num, String qualified)
        {
            TypeReference t = GlobalVM::Get(GlobalVM::Get(qualified));

            if (t == TypeReference::Fail)
            {
                const char* unk = "Unknown type: ";

                CENative total = strlen(unk) + strlen(qualified) + 1;

                char* buff = Allocator<char>::NativeAlloc(total);

                strcpy(buff, unk);
                strcat(buff, qualified);

                fprintf(stderr, "FATAL: %s\n", buff);

                Allocator<char>::NativeFree(buff);

                CE_ASSERT(false, "See above.");
            }

            return VMObject {
                .TrueType = t,
                .Managed = true,
                .Type = VMObjectType::VMMObject,
                .Pointer = num  
            };
        }

        static VMObject NewPointer(VMPtr num, bool managed)
        {
            return VMObject {
                .TrueType = TPointer,
                .Managed = managed,
                .Type = VMObjectType::VMPtr,
                .Pointer = num  
            };
        }
        
        static VMObject NewSingle(VMFloat num)
        {
            return VMObject {
                .TrueType = TSingle,
                .Managed = false,
                .Type = VMObjectType::VMFloat,
                .Single = num  
            };
        }
    };
};