#pragma once

#include <mutex>

#include <jni.h>

class Java {
private:
	JavaVM* vm = nullptr;
	JNIEnv* environment = nullptr;
public:
	bool init() {
		jsize VMCount = 0;

		jint result = JNI_GetCreatedJavaVMs(&vm, 1, &VMCount);
		if (result != JNI_OK || VMCount == 0) {
			OutputDebugStringA("Java VM not found\n");
			return false;
		}
		OutputDebugStringA("Got Java VM\n");

		result = vm->GetEnv(reinterpret_cast<void**>(&environment), JNI_VERSION_1_8);
		if (result == JNI_OK) {
			OutputDebugStringA("Thread already attached\n");
			return true;
		}
		else if (result != JNI_EDETACHED) {
			OutputDebugStringA("GetEnv didnt return JNI_EDETACHED\n");
			return false;
		}

		result = vm->AttachCurrentThread(reinterpret_cast<void**>(&environment), nullptr);
		if (result != JNI_OK || environment == nullptr) {
			OutputDebugStringA("Failed to attach thread\n");
			return false;
		}
		OutputDebugStringA("Attached thread\n");

		return true;
	}
};

inline auto java = std::make_unique<Java>();