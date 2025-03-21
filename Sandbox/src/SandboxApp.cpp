#include "Nameless.h"
#include <Nameless/Renderer/Geometry.h>

class ExampleLayer : public Nameless::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_OrthoCamera(-1.92f, 1.92f, -1.08f, 1.08f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Nameless::VertexArray::Create());

		m_PrismVertexArray.reset(Nameless::VertexArray::Create());
		
		float prismVertices[28 * 3] =
		{
			-0.3f,  0.0f, 0.0f,
			 0.0f, -0.7f, 0.0f,
			 0.3f,  0.0f, 0.0f,
			-0.3f,  0.0f, 0.0f,

			 0.3f,  0.0f, 0.0f,
			 0.0f,  0.7f, 0.0f,
			-0.3f,  0.7f, 0.0f,
		};

		std::shared_ptr<Nameless::VertexBuffer> prismVertexBuffer;
		prismVertexBuffer.reset(Nameless::VertexBuffer::Create(prismVertices, sizeof(prismVertices)));

		prismVertexBuffer->SetLayout({
			{ Nameless::ShaderDataType::Float3, "a_Position" }
			});

		m_PrismVertexArray->AddVertexBuffer(prismVertexBuffer);

		unsigned int prismIndices[7] = { 0, 1, 2, 3, 4, 5, 6 };

		std::shared_ptr<Nameless::IndexBuffer> prismIndexBuffer;
		prismIndexBuffer.reset(Nameless::IndexBuffer::Create(prismIndices, sizeof(prismIndices) / sizeof(uint32_t)));
		m_PrismVertexArray->SetIndexBuffer(prismIndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;

			out vec3 n_Position;

			void main()
			{
				n_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 n_Position;
			
			void main()
			{
				color =  vec4(0, 0.7, 0, 1.0);
			}
		)";

		m_Shader.reset(new Nameless::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate() override
	{
		if (Nameless::Input::IsKeyPressed(NMLS_KEY_LEFT))
			m_CameraPosition.x += m_CameraMovmentSpeed;
		else if (Nameless::Input::IsKeyPressed(NMLS_KEY_RIGHT))
			m_CameraPosition.x -= m_CameraMovmentSpeed;

		if (Nameless::Input::IsKeyPressed(NMLS_KEY_UP))
			m_CameraPosition.y -= m_CameraMovmentSpeed;
		else if (Nameless::Input::IsKeyPressed(NMLS_KEY_DOWN))
			m_CameraPosition.y += m_CameraMovmentSpeed;

		if (Nameless::Input::IsKeyPressed(NMLS_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed;
		else if (Nameless::Input::IsKeyPressed(NMLS_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed;

		Nameless::RenderCommand::SetClearColor({ 0.3f, 0.3f, 0.3f, 1.0f });
		Nameless::RenderCommand::Clear();

		Nameless::Renderer::BeginScene(m_OrthoCamera);
		{
			m_OrthoCamera.SetPosition(m_CameraPosition);
			m_OrthoCamera.SetRotation(m_CameraRotation);
			Nameless::Renderer::Submit(m_Shader, m_PrismVertexArray);
		}
		Nameless::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Nameless::Event& event) override
	{
	}

private:
	std::shared_ptr<Nameless::Shader> m_Shader;
	std::shared_ptr<Nameless::VertexArray> m_VertexArray;
	std::shared_ptr<Nameless::VertexArray> m_PrismVertexArray;

	Nameless::OrthographicCamera m_OrthoCamera;

	glm::vec3 m_CameraPosition;
	float m_CameraMovmentSpeed = 0.03f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 1.0f;
};

class Sandbox : public Nameless::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Nameless::Application* Nameless::CreateApplication()
{
	return new Sandbox();
}