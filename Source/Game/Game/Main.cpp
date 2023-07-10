#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include <iostream>
#include <vector>

using namespace std;

class Star
{
public:
	Star(const kiko::Vector2& pos, kiko::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel;

		if (m_pos.x >= width)
			m_pos.x = 0;

		if (m_pos.y > height)
			m_pos.y = 0;
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::Vector2 m_pos;
	kiko::Vector2 m_vel;

};

using vec2 = kiko::Vector2;

int main(int argc, char* argv[])
{
	kiko::seedRandom((unsigned int)time(nullptr));

	kiko::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800, 600);

	vector <Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(renderer.GetWidth()), kiko::randomf(kiko::random(renderer.GetHeight()))));
		kiko::Vector2 vel(kiko::randomf(1,4), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	while (true)
	{
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		
		//draw
		kiko::Vector2 vel(1.0f, 0.3f);

		for (auto& star : stars)
		{

			star.Update(renderer.GetWidth(), renderer.GetHeight());

			//point.x += 1;
			//point.y += 0.3f;

			renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			star.Draw(renderer);
		}
		
		//for (int i = 1; i < 1000; i++)
		//{
		//	kiko::Vector2 pos(kiko::randomf(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
		//	
		//	//int x = kiko::random(renderer.GetWidth());
		//	//int y = kiko::random(renderer.GetHeight());
		//	renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
		//	renderer.DrawPoint(pos.x,pos.y);
		//	//renderer.DrawPoint(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
		//	//renderer.DrawLine(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()), kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
		//}
		
		renderer.EndFrame();
	}

	return 0;

	/*
	kiko::CreateWindow("CSC196", 800, 600);
	cin.get(); //pause
	*/

	/*
	kiko::g_memoryTracker.DisplayInfo();
	int* p = new int;
	kiko::g_memoryTracker.DisplayInfo();
	delete p;
	kiko::g_memoryTracker.DisplayInfo();

	kiko::Time timer;
	for (int i = 0; i < 1000000; i++) {}

	cout << timer.GetElapsedSeconds() << endl;
	*/

	/*/
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000; i++)
	{
		int* p = new int;
		delete p;
	}
	auto end = std::chrono::high_resolution_clock::now();

	cout << std::chrono::duration_cast<std::chrono::microseconds>(start - end).count() << endl;
	*/

	/*int* p = new int;
	delete p;

	cout << kiko::getFilePath() << endl;
	kiko::setFilePath("Assets");
	cout << kiko::getFilePath() << endl;
	size_t size;
	kiko::getFileSize("Game.txt", size);
	cout << size << endl;

	std::string s;
	kiko::readFile("Game.txt", s);
	cout << s << endl;

	kiko::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 3; i++)
	{
		cout << kiko::random(5, 10) << endl;
	}*/
}
