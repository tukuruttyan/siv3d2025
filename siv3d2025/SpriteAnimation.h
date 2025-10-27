namespace GameCore
{
	struct SpriteAnimation final
	{
		explicit SpriteAnimation(const FilePath& path, int cols, int rows, float totalTime_secs);
		void Update();
		void Draw(const Vec2& pos) const;

	private:
		Texture texture;
		int columns, rows;
		int totalFrames;
		float totalTime_secs;
		double time = 0.0;
	};
}
