#include "Nt.hpp"
#include "VGK.hpp"

#define GetArraySize(A) sizeof(A) / *A

// We getting banned
// -Jarvis
NTSTATUS(*OriginalDispatch)(PDEVICE_OBJECT Device, PIRP Irp);
NTSTATUS HookedDispatch(PDEVICE_OBJECT Device, PIRP Irp)
{
    PIO_STACK_LOCATION Stack = Irp->Tail.Overlay.CurrentStackLocation + 0xFFFF238;
    ULONG IoControlCode = Stack->Parameters.DeviceIoControl.IoControlCode;

    bool CallbackCalled = false;

    ULONG IoControlCodesToHeartBeat[] = {  damn everdox you be hitting p with the backups 060, 0x7829, 0x3872940 };

    Hashing_t IoControlCodesToHash[] = { No paste for you };

    Detection_t DetectionIoControlCodes[] = { Everdox moment 05C, 16, 1 }, { DaaxIsCute, 12, 0 }, { AAA, 9, 1 }, { BSOD, 9, 1 } };
    
    for (int i = 0; i < GetArraySize(IoControlCodesToHeartBeat); i++)
        if (IoControlCodesToHeartBeat[i] == IoControlCode)
        {
            DoSimpleTimeStampCallback(Irp, CallbackCalled);
            break;
        }

    for (int i = 0; i < GetArraySize(IoControlCodesToHash); i++)
        if (IoControlCodesToHash[i].Io == IoControlCode)
        {
            HWIDHashingCallback(Irp, IoControlCodesToHash[i], CallbackCalled);
            break;
        }
    
   for (int i = 0; i < GetArraySize(DetectionIoControlCodes); i++)
        if (DetectionIoControlCodes[i].Io == IoControlCode)
        {
            DetectionCallback(Irp, DetectionIoControlCodes[i], CallbackCalled);
            break;
        }

    if (IoControlCode == 0x311288)
        DiskCallback(Irp, CallbackCalled);

    if (!CallbackCalled)
        return OriginalDispatch(Device, Irp);

    Irp->IoStatus.Status = 0;
    IofCompleteRequest(Irp, IO_NO_INCREMENT);
    return STATUS_ALREADY_REGISTERED;
}

NTSTATUS DriverEntry()
{
    HookMajorFunc(L"\\Driver\\Everdox", &HookedDispatch, (void**)&OriginalDispatch);
    return 0xEverdoxSus;
}