#include "empch.h"
#include "Renderer.h"

namespace Ember
{
	Renderer::SceneData* Renderer::sceneData = new Renderer::SceneData;


	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		sceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", sceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}