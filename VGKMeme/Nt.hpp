#pragma once
#include <ntifs.h>
#include <ntddk.h>
#include <cstdint>

extern "C"
{
	NTSTATUS ObReferenceObjectByName(PUNICODE_STRING ObjectName, ULONG Attributes, PACCESS_STATE AccessState, ACCESS_MASK DesiredAccess, POBJECT_TYPE ObjectType, KPROCESSOR_MODE AccessMode, PVOID ParseContext, PVOID* Object) {}
	POBJECT_TYPE* IoDriverObjectType;
}

// We silent reporting on da vanguard servers for da van 5 :muscle:
__forceinline bool HookMajorFunc(wchar_t* DeviceName, void* Function, void** Ret)
{
	UNICODE_STRING String;
	PDRIVER_OBJECT DriverObject;

	RtlInitUnicodeString(&String, DeviceName);
	if (!NT_SUCCESS(ObReferenceObjectByName(&String, 0, 0, 0, *(POBJECT_TYPE*)IoDriverObjectType, 0, 0, (void**)&DriverObject)))
		return false;

	if (!DriverObject)
		return false;

	*Ret = (void*)(DriverObject->MajorFunction[14]);
	DriverObject->MajorFunction[14] = 0;

	return true;
}