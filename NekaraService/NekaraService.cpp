#include "pch.h"
#include "NekaraService.h"

NS::NekaraService* _ns;

extern "C" {
    __declspec(dllexport) void NS_WithoutSeed() {
        _ns = new NS::NekaraService();
    }

    __declspec(dllexport) void NS_WithSeed(int _seed) {
        _ns = new NS::NekaraService(_seed);
    }

    __declspec(dllexport) void NS_CreateTask() {
        assert(_ns != NULL && "Nekara Testing Service not Initialized");
        _ns->CreateThread();
    }

    __declspec(dllexport) void NS_StartTask(int _threadID) {
        assert(_ns != NULL && "Nekara Testing Service not Initialized");
        _ns->StartThread(_threadID);
    }

    __declspec(dllexport) void NS_EndTask(int _threadID) {
        assert(_ns != NULL && "Nekara Testing Service not Initialized");
        _ns->EndThread(_threadID);
    }

    __declspec(dllexport) void NS_CreateResource(int _resourceID) {
        assert(_ns != NULL && "Nekara Testing Service not Initialized");
        _ns->CreateResource(_resourceID);
    }

    __declspec(dllexport) void NS_DeleteResource(int _resourceID) {
        assert(_ns != NULL && "Nekara Testing Service not Initialized");
        _ns->DeleteResource(_resourceID);
    }

    __declspec(dllexport) void NS_BlockedOnResource(int _resourceID) {
        assert(_ns != NULL && "Nekara Testing Service not Initialized");
        _ns->BlockedOnResource(_resourceID);
    }

    __declspec(dllexport) void NS_SignalUpdatedResource(int _resourceID) {
        assert(_ns != NULL && "Nekara Testing Service not Initialized");
        _ns->SignalUpdatedResource(_resourceID);
    }

    __declspec(dllexport) int NS_GenerateResourceID() {
        assert(_ns != NULL && "Nekara Testing Service not Initialized");
        return _ns->GenerateResourceID();
    }

    __declspec(dllexport) int NS_GenerateThreadTD() {
        assert(_ns != NULL && "Nekara Testing Service not Initialized");
        return _ns->GenerateThreadTD();
    }

    __declspec(dllexport) bool NS_CreateNondetBool() {
        assert(_ns != NULL && "Nekara Testing Service not Initialized");
        return _ns->CreateNondetBool();
    }

    __declspec(dllexport) int NS_CreateNondetInteger(int _maxvalue) {
        assert(_ns != NULL && "Nekara Testing Service not Initialized");
        return _ns->CreateNondetInteger(_maxvalue);
    }

    __declspec(dllexport) void NS_ContextSwitch() {
        assert(_ns != NULL && "Nekara Testing Service not Initialized");
        _ns->ContextSwitch();
    }

    __declspec(dllexport) void NS_WaitforMainTask() {
        assert(_ns != NULL && "Nekara Testing Service not Initialized");
        _ns->WaitforMainTask();
    }

    __declspec(dllexport) bool NS_Dispose() {
        _ns = NULL;
        return true;
    }
}