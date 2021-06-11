#include "vrviewer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	delete[] filepath;
}

void Renderer::Render()
{
	renderer->SetShowFloor(false);

	renderer->SetBackground(0.0, 0.0, 0.0);
	renderWindow->AddRenderer(renderer.Get());
	renderer->AddActor(actor.Get());
	iren->SetRenderWindow(renderWindow.Get());
	renderer->SetActiveCamera(cam.Get());

	renderWindow->SetDesiredUpdateRate(350.0);
	iren->SetDesiredUpdateRate(350.0);
	iren->SetStillUpdateRate(350.0);

	renderer->RemoveCuller(renderer->GetCullers()->GetLastItem());

	reader->SetFileName(filepath);

	mapper->SetInputConnection(reader->GetOutputPort());
	actor->SetMapper(mapper.Get());

	renderWindow->Initialize();
	if (renderWindow->GetHMD())
	{
		renderer->ResetCamera();
		renderWindow->Render();

		renderWindow.Get();
		iren->Start();
	}
}
