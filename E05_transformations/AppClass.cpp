#include "AppClass.h"
void Application::InitVariables(void)
{
	//init the mesh
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(1.0f, C_BLACK);
	//m_pMesh->GenerateSphere(1.0f, 5, C_WHITE);
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	
	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(0.5f, 0.5f, 0.5f));
	static float value = 0.0f;
	matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(value, 2.0f, 3.0f));
	//value += 0.01f;

	matrix4 m4Model = m4Translate * m4Scale;
	//matrix4 m4Model = m4Scale * m4Translate;
	static float currentLocationAroundCircle = 0.0f;
	static float angle = 0.0f;

	for (int i = 0; i < 11; i++) {
		
		if (i == 0 || i == 10) {
			for (int j = 1; j < 3; j++) {
				m4Translate = glm::translate(IDENTITY_M4, vector3((float)i - 5.5f + cos(angle), (float)j- 1.0f + sin(angle), 3.0f));
				m4Model = m4Scale * m4Translate;
				m_pMesh->Render(m4Projection, m4View, m4Model);
			}
		}
		if (i==1 || i == 9){
			int j = i;
			if (i == 9) j = 1;
			m4Translate = glm::translate(IDENTITY_M4, vector3((float)i - 5.5f + cos(angle), (float)j + 2.0f + sin(angle), 3.0f));
			m4Model = m4Scale * m4Translate;
			m_pMesh->Render(m4Projection, m4View, m4Model);
		}
		if (i == 2 || i == 8) {
			for (int j = 0; j < 7; j++) {
				if (j == 2 || j== 5) continue;
				m4Translate = glm::translate(IDENTITY_M4, vector3((float)i - 5.5f + cos(angle), (float)j + sin(angle), 3.0f));
				m4Model = m4Scale * m4Translate;
				m_pMesh->Render(m4Projection, m4View, m4Model);
			}
		}
		if (i == 3 || i == 7) {
			for (int j = 0; j < 7; j++) {
				if (j == 1 || j == 3 || j == 4) continue;
				m4Translate = glm::translate(IDENTITY_M4, vector3((float)i - 5.5f + cos(angle), (float)j - 1.0f + sin(angle), 3.0f));
				m4Model = m4Scale * m4Translate;
				m_pMesh->Render(m4Projection, m4View, m4Model);
			}
		}
		if (i == 4 || i == 6) {
			for (int j = 0; j < 6; j++) {
				if (j == 1 || j == 3) continue;
				m4Translate = glm::translate(IDENTITY_M4, vector3((float)i - 5.5f + cos(angle), (float)j - 1.0f + sin(angle), 3.0f));
				m4Model = m4Scale * m4Translate;
				m_pMesh->Render(m4Projection, m4View, m4Model);
			}
		}
		if (i == 5) {
			for (int j = 0; j < 4; j++) {
				if (j == 1) continue;
				m4Translate = glm::translate(IDENTITY_M4, vector3((float)i - 5.5f + cos(angle), (float)j + 1.0f + sin(angle), 3.0f));
				m4Model = m4Scale * m4Translate;
				m_pMesh->Render(m4Projection, m4View, m4Model);
			}
		}

		m4Translate = glm::translate(IDENTITY_M4, vector3((float)i - 5.5f + cos(angle), 2.0f + sin(angle), 3.0f));
		m4Model = m4Scale * m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
	}
	currentLocationAroundCircle += 0.1f;
	angle = 2 * PI * (currentLocationAroundCircle / 12);


	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}