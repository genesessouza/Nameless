#include "nmlspch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Nameless/Input/Input.h"

namespace Nameless {
#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		NMLS_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float square[3 * 4] =
		{
			-0.8f, -0.9f, 0.0f,
			 0.8f, -0.9f, 0.0f,
			 0.8f,  0.9f, 0.0f,
			-0.8f,  0.9f, 0.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(square, sizeof(square)));

		BufferLayout squareLayout = {
			{ ShaderDataType::Float3, "a_Position" }
		};

		vertexBuffer->SetLayout(squareLayout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 n_Position;

			void main()
			{
				n_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 n_Position;
			in vec4 n_Color;
			
			void main()
			{
				color =  vec4(0.7, 0.1, 0.2, 1.0);
			}
		)";
		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		m_PrismVertexArray.reset(VertexArray::Create());

		float prismVertices[7 * 7] =
		{
			-0.15f,  0.0f, 0.0f,
			 0.00f, -0.5f, 0.0f,
			 0.15f,  0.0f, 0.0f,
			-0.15f,  0.0f, 0.0f,

			 0.15f,  0.0f, 0.0f,
			 0.00f,  0.5f, 0.0f,
			-0.15f,  0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> prismVertexBuffer;
		prismVertexBuffer.reset(VertexBuffer::Create(prismVertices, sizeof(prismVertices)));

		prismVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});

		m_PrismVertexArray->AddVertexBuffer(prismVertexBuffer);

		unsigned int prismIndices[7] = { 0, 1, 2, 3, 4, 5, 6 };

		std::shared_ptr<IndexBuffer> prismIndexBuffer;
		prismIndexBuffer.reset(IndexBuffer::Create(prismIndices, sizeof(prismIndices) / sizeof(uint32_t)));
		m_PrismVertexArray->SetIndexBuffer(prismIndexBuffer);

		std::string vertexSrc2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 n_Position;

			void main()
			{
				n_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 n_Position;
			
			void main()
			{
				color =  vec4(0, 0.7, 0, 1.0);
			}
		)";

		m_Shader2.reset(new Shader(vertexSrc2, fragmentSrc2));
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			if (e.Handled())
				break;
			(*--it)->OnEvent(e);
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.3f, 0.3f, 0.3f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader2->Bind();
			m_PrismVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_PrismVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}