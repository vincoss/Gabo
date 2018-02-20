/*
 * GaboLoop.h
 *
 * Created: 20/02/2018 5:41:18 PM
 *  Author: Ferdinand
 */ 


#ifndef GABOLOOP_H_
#define GABOLOOP_H_



int isRunning;B

void Loop(void)
{
	const int ticksPerSecond = 25;
	const int skipTicks = 1000 / ticksPerSecond;
	const int maxFrameSkip = 5;

	unsigned long long nextGameTick = GetTickCount();

	while (isRunning)
	{
		int loops = 0;

		while (GetTickCount() > nextGameTick && loops < maxFrameSkip)
		{
			OnUpdateGame();

			nextGameTick += skipTicks;
			loops++;
		}

		// Usage view_position = position + (speed * interpolation)
		float interpolation = (GetTickCount() + skipTicks - nextGameTick) / (float)skipTicks;
		OnRenderGame(interpolation);
	}
}

void OnUpdateGame(void)
{
	printf("OnUpdateGame");
}

void OnRenderGame(float interpolation)
{
	printf("OnRenderGame %f", interpolation);
}



#endif /* GABOLOOP_H_ */