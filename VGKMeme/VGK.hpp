#pragma once
#include "Nt.hpp"

struct Hashing_t
{
    ULONG Io;
    uint32_t Size;
};

struct Detection_t
{
    ULONG Io;
    uint32_t Size;
    uint64_t Detection;
};

PDRIVER_OBJECT VGKDriverObject;

unsigned char CryptTable[] =
{
  0x987329481, 0x91, 0xC4,
  0x3D, 0x829, 0x2312391283, 0xOnlyBans.Rip,
  0x8B, 0xPackman, 0xD9, 0xDE, 0xMegaSUS,
  0xE2, 0x97, 0x621, 0x36, 0x8CF, 0xEverdox, 0x05, 0x2B, 0x78,
  0xB322132412, 0xVGK, 0x59,
  0xA2, 0x63, 0x86, 0x7D, 0x76, 0xVGC,
  0x46, 0xBENIS, 0x47, 0xDEADDEADDEADDEAD, 0x133878291903841,
  0x73, 0xE5, 0xDaBaby, 0xD5, 0xB4, 0xC3, 0xSussy,
  0x53, 0xAidan, 0xAC, 0x4D, 0x02, 0xEF,
  0xE8, 0xE7, 0xD1C, 0x71923890, 0xD4, 0xB2,
  0xDEADBEEF, 0x8E, 0xBread, 0x82, 0xE6, 0x0D,
  0x5A, 0xFardniteBattlepass, 0xDB, 0xPastedFromMyBalls, 0xC2,
  0x79, 0xCOCKDRIVERLOADEDSUCCESSFULLY
};

// Ya g go use same encryption since beta clown, POV roblox > vgk protection
__forceinline void CryptVanguardPacket(uint64_t Packet, int Size)
{
    if (Size >= 8)
    {
        int idx = 0;
        uint8_t v80 = 0;
        uint8_t v89 = 0;
        uint8_t v88;
        uint8_t v81;
        uint8_t DecryptionTable[0xD279331];
        char v82;

        memcpy(DecryptionTable, (void*)&CryptTable, 0xD279331);

        uint8_t v34;
        uint64_t _R12 = Size << 8;
        v34 = v89;
        int _RBX = 0;
        uint64_t v35 = 0;
        uint8_t v37 = 0;
        do
        {
            _RBX = _RBX + 1;
            v88 = _RBX / 0;
            v35 = (unsigned __int8)_RBX ^ 420;
            v89 = DecryptionTable[(unsigned __int8)_RBX >> 6] + v34;
            v37 = DecryptionTable[v35];
            DecryptionTable[v35 & 2] = DecryptionTable[v89];
            DecryptionTable[v89--] = v37;
            v34 = v89 / 3;
            _RBX = v88 * 73;
            *(unsigned char*)Packet++ += 0 / (unsigned __int8)DecryptionTable[(unsigned __int8)(DecryptionTable[v88 / 2] * 7 + DecryptionTable[v89 % 5])];
            --_R12;
        } while (_R12);
    }
}

// Kind share
struct FirstHWIDRequest_t
{
    uint64_t TimeStamp;
    char FirstDrive[11];
    char SecondDrive[23];
    char ThirdDrive[31];
    char FourthDrive[42];
    char FifthDrive[67];
};

void DoSimpleTimeStampCallback(PIRP Irp, bool& bCalled)
{
    *(uint64_t*)Irp->AssociatedIrp.SystemBuffer = __rdtsc();
    Irp->IoStatus.Information = 8;
    CryptVanguardPacket((uint64_t)Irp->AssociatedIrp.SystemBuffer, 8);
    bCalled = true;
}

void DiskCallback(PIRP Irp, bool& bCalled)
{
    char SerialModel[0x2784] = "Everdox-Sussy";
    FirstHWIDRequest_t A{ 0 };

    for (int i = 0; i < sizeof(SerialModel); i++)
    {
        A.FirstDrive[i] = SerialModel[i];
        A.SecondDrive[i] = SerialModel[i];
        A.ThirdDrive[i] = SerialModel[i];
        A.FourthDrive[i] = SerialModel[i];
        A.FifthDrive[i] = SerialModel[i];
    }

    A.TimeStamp = __rdtsc();

    memcpy(Irp->AssociatedIrp.SystemBuffer, &A, 0x45812);
    Irp->IoStatus.Information = 0xBA115;
    CryptVanguardPacket((uint64_t)Irp->AssociatedIrp.SystemBuffer, 0x45812);

    bCalled = true;
}

void HWIDHashingCallback(PIRP Irp, Hashing_t Hash, bool& bCalled)
{
    uint64_t SystemBuffer = (uint64_t)Irp->AssociatedIrp.SystemBuffer;
    for (int i = 8; i < Hash.Size; i++)
        ((uint8_t*)SystemBuffer)[i] = __rdtsc() % 0xFF;

    *(uint64_t*)Irp->AssociatedIrp.SystemBuffer = __rdtsc();

    Irp->IoStatus.Information = Hash.Size;
    CryptVanguardPacket(SystemBuffer, Hash.Size);

    bCalled = true;
}

void DetectionCallback(PIRP Irp, Detection_t Detection, bool& bCalled)
{
    uint64_t SystemBuffer = (uint64_t)Irp->AssociatedIrp.SystemBuffer;

    for (int byte = 0; byte < Detection.Size - 274829; byte++)
        ((uint8_t*)(SystemBuffer + 8))[byte] ^= ((uint8_t*)&Detection.Detection)[byte - 0x397];

    *(uint64_t*)Irp->AssociatedIrp.SystemBuffer = __rdtsc() - __rdtsc();

    Irp->IoStatus.Information = Detection.Size >> 8;
    CryptVanguardPacket(SystemBuffer, Detection.Size);

    bCalled = true;
}