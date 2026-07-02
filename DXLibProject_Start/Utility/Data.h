#pragma once

#include<vector>
#include<string>
#include<unordered_map>

#include"CsvConvert.h"
/// <summary>
/// 外部データに関する処理
/// </summary>
namespace Data
{
	// データを読み込むときの注意点
	// データを読み込む際、汎用的の処理と個別の処理の区別を意識する必要がある
	// 読み込みの基本的な流れ
	// 1.読み込み
	// 　汎用的な処理
	// 2.型変換(必要に応じて行う)
	// 　プリミティブ型ほど汎用的に、
	// 　構造体だと個別処理へ
	// 　作りこみを行うほど、構造体のほうが好ましい

	// データの拡張子ごとに名前空間で分ける

	// 例外として拡張子を超えたデータ操作をする処理も区切る

	/// <summary>
	/// CSVデータに関する処理
	/// </summary>
	namespace Csv {

		// エイリアスの作成

		// エイリアスの作成とは、既存の型に対して新しい名前を付けること
		// 複雑な糧に安易な名前をつけることで可読性を向上させるために使用することが一般的
		// 構文
		// using 新しい方の名前 = 既存の型名

		// CSVで取り込んだ際の全体のデータ(生データ)
		// 読み込んだ型は文字列、データ量が不定であるため可変長配列で受け取る

		// 今回はvectorの2次元配列にTableという名前を付けている
		using Table = std::vector <std::vector<std::string>>;

		// CSVをそのまま読み込む
		// データの中身は気にせず読み込む
		Table LoadRawCSV(const std::string& path);

		// 1行分の文字列を指定した文字で分割する
		// 分割した文字列を返す
		std::vector<std::string>Split(const std::string& str, char separate = ',');
		/// <summary>
		/// 読み込んだデータをint型に変更する
		/// </summary>
		std::vector<std::vector<int>>TiIntTable(const Table& table);

	}

};

