#pragma once
#include<random>
/// <summary>
/// 乱数を生成するクラス
/// 以下のページを参考に作成
/// </summary>
class MyRandom
{
public:
	/// <summary>
	/// 疑似乱数の初期化(起動時に1回)
	/// </summary>
	static void Init();

	/// <summary>
	/// 引数の範囲内での乱数を生成(引数を含む)
	/// </summary>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>ランダムで生成した値
	static int Int(int min, int max);
	/// <summary>
	/// 引数の範囲内での乱数を生成(引数を含む)
	/// </summary>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>ランダムで生成した値
	static float Float(float min, float max);
	/// <summary>
	/// 0.0f ～ 1.0f の乱数を生成
	/// </summary>
	/// <returns>ランダムで生成した値
	static float Float01();
	/// <summary>
	/// 確率判定
	/// </summary>
	/// <param name="min">確率</param>
	/// <returns>確率内ならtrue
	static bool Judge(float percent);
private:
	static std::mt19937& Engine();

};

