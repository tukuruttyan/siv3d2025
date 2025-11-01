namespace GameCore
{
	class SpriteAnimation final
	{
	public:
		SpriteAnimation(const FilePath& path, int cols, int rows, double totalTime_secs);

		void Draw(const Vec2& pos);
		void Draw(const Vec2& pos, const SizeF& size);

	private:
		Texture texture;
		int columns;
		int rows;
		int totalFrames;
		double totalTime_secs;
		double time = 0.0;
	};
}
