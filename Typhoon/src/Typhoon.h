#pragma once

// For use by Typhoon applications

#include "Typhoon/Core/Application.h"
#include "Typhoon/Core/Layer.h"
#include "Typhoon/Core/Log.h"

#include "Typhoon/Core/Timestep.h"

#include "Typhoon/Core/Input.h"
#include "Typhoon/Core/KeyCodes.h"
#include "Typhoon/Core/MouseButtonCodes.h"

#include "Typhoon/ImGui/ImGuiLayer.h"

// ---Renderer-----------------------------
#include "Typhoon/Renderer/OrthographicCameraController.h"
#include "Typhoon/Renderer/Renderer.h"
#include "Typhoon/Renderer/RenderCommand.h"
// ----------------------------------------

// ---Resources----------------------------
#include "Typhoon/Renderer/Resources/Buffer.h"
#include "Typhoon/Renderer/Resources/Shader.h"
#include "Typhoon/Renderer/Resources/Texture.h"
#include "Typhoon/Renderer/Resources/Array.h"
// ----------------------------------------

// ---Camera's-----------------------------
#include "Typhoon/Renderer/OrthographicCamera.h"
// ----------------------------------------

// ---Entry Point--------------------------
#include "Typhoon/Core/EntryPoint.h"
// ----------------------------------------