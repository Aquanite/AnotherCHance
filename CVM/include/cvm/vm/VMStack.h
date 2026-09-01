#ifndef CHANCE_VM_VMSTACK_H
#define CHANCE_VM_VMSTACK_H

#include <chance/types/generic/NativeStack.h>
#include <chance/types/VMObject.h>

namespace CE::VM
{
    class VMStack : NativeStack<VMObject>
    {
    private:
        using base = NativeStack<VMObject>;
    
    public:
        using base::Push;
        using base::Pop;
        using base::Capacity;
        using base::Length;
        using base::Data;
        using base::Pin;
        using base::Unpin;
        using base::IsEmpty;
        using base::IsFull;
        using base::IsPinned;
        using base::Grow;
        using base::Truncate;
        using base::Clear;
        using base::operator[];
    
    public:
        VMStack() : base(0) {}
    };
};

#endif // CHANCE_VM_VMSTACK_H