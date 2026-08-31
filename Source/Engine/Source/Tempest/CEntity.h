#pragma once


namespace Tempest {
    class CEntity {
    public:
        virtual ~CEntity() {
        }

        virtual void Release() {
            this->~CEntity();
            DeallocateMemoryEx(this);
        }
    };
}



