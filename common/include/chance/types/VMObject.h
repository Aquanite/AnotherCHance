#pragma once

#include <chance/vm/GlobalVM.h>
#include <string.h>


namespace CE
{
    struct alignas(0x8) VMObject
    {
        static Nullable<CE::Type> TI32;
        static Nullable<CE::Type> TI64;
        static Nullable<CE::Type> TINative;
        static Nullable<CE::Type> TPointer;
        static Nullable<CE::Type> TSingle;

        CE::Type TrueType;
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
            TI32     = GlobalVM::ResolveType(GlobalVM::Get("System.I32"));
            TI64     = GlobalVM::ResolveType(GlobalVM::Get("System.I64"));
            TINative = GlobalVM::ResolveType(GlobalVM::Get("System.INative"));
            TPointer = GlobalVM::ResolveType(GlobalVM::Get("System.Pointer"));
            TSingle  = GlobalVM::ResolveType(GlobalVM::Get("System.Single"));
            CE_ASSERT(!TI32     .IsNull(), "TI32 is null!");
            CE_ASSERT(!TI64     .IsNull(), "TI64 is null!");
            CE_ASSERT(!TINative .IsNull(), "TINative is null!");
            CE_ASSERT(!TPointer .IsNull(), "TPointer is null!");
            CE_ASSERT(!TSingle  .IsNull(), "TSingle is null!");
        }

        static VMObject NewI32(VMi32 num)
        {
            return VMObject {
                .TrueType = TI32.GetValue(),
                .Managed = false,
                .Type = VMObjectType::VMi32,
                .Integer = num
            };
        }

        static VMObject NewI64(VMi64 num)
        {
            return VMObject {
                .TrueType = TI64.GetValue(),
                .Managed = false,
                .Type = VMObjectType::VMi64,
                .LongInteger = num  
            };
        }

        static VMObject NewNative(VMNative num)
        {
            return VMObject {
                .TrueType = TINative.GetValue(),
                .Managed = false,
                .Type = VMObjectType::VMNative,
                .NativeInteger = num  
            };
        }

        static VMObject NewObject(VMPtr num, String qualified)
        {
            Nullable<CE::Type> t = GlobalVM::ResolveType(GlobalVM::Get(qualified));

            if (t.IsNull())
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
                .TrueType = t.GetValue(),
                .Managed = true,
                .Type = VMObjectType::VMMObject,
                .Pointer = num  
            };
        }

        static VMObject NewPointer(VMPtr num, bool managed)
        {
            return VMObject {
                .TrueType = TPointer.GetValue(),
                .Managed = managed,
                .Type = VMObjectType::VMPtr,
                .Pointer = num  
            };
        }
        
        static VMObject NewSingle(VMFloat num)
        {
            return VMObject {
                .TrueType = TSingle.GetValue(),
                .Managed = false,
                .Type = VMObjectType::VMFloat,
                .Single = num  
            };
        }
    };
};