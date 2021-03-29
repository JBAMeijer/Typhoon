#pragma once

// For use by Hazel applications

#include "Hazel/Core/Application.h"
#include "Hazel/Core/Layer.h"
#include "Hazel/Core/Log.h"

#include "Hazel/Core/Timestep.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseButtonCodes.h"

#include "Hazel/ImGui/ImGuiLayer.h"

// ---Renderer-----------------------------
#include "Hazel/Renderer/OrthographicCameraController.h"
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Renderer/RenderCommand.h"
// ----------------------------------------

// ---Resources----------------------------
#include "Hazel/Renderer/Resources/Buffer.h"
#include "Hazel/Renderer/Resources/Shader.h"
#include "Hazel/Renderer/Resources/Texture.h"
#include "Hazel/Renderer/Resources/Array.h"
// ----------------------------------------

// ---Camera's-----------------------------
#include "Hazel/Renderer/OrthographicCamera.h"
// ----------------------------------------

// ---Entry Point--------------------------
#include "Hazel/Core/EntryPoint.h"
// ----------------------------------------