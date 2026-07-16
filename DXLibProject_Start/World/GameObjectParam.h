#pragma once
#include"../Utility/Vector3.h"

// 外部データからゲーム内のパラメータにアクセスする際の注意点
// CSVやJsonからデータを取得してゲーム内のパラメータに設定する際に、
// どの型にするのか、どういう構造体にするのかという情報がは変換の際には必要になる
// →列挙体に変換する場合、CsvConvert.h等でインクルードする必要がある
// →構造体に変換する場合、FromCsv.h等でインクルードする必要がある
// クラスの内部で定義されている列挙体ｍ構造体があると、
// 外部データ対応重ねることで循環参照を引き起こす原因になってしまう
// 
// 外部データ対応をする際に、
// クラス内部のパラメータは専用のヘッダーに移しておくと循環参照を回避できる
// GameObjectクラス内ではｍクラス内に以下の列挙体・構造体が定義されている
// ・CollisionTag
// ・CollisionType
// ・CpllisionData
//ここでは、データと実行時にオブジェクトになるかどうかで分類する
// CollisionTagとCollisionTypeがデータ、
// CollisionDataは実行時にオブジェクトになるもの、
// データとして扱われる2留津は別ヘッダーに移しておくとよい
// 
// CollisionDataを別ヘッダーに移さない理由は以下
// ・状態を持つかどうか、持つ場合は移さないほうが良い
// ・他オブジェクトとの関係を持つかどうか、持つ場合は移さないほうが良い
// ・メモリを所有するかどう
//



	/// <summary>
		/// 衝突判定時にGameObjectクラスを区別するときに使用
		/// </summary>
	enum class CollisionTag {
		Invalid = -1,
		None,
		Player,
		Dragon,
		Enemy,
		Wall,
		Stage,
		Barrier,
	};
	enum class CollisionType {
		Invalid = -1,
		Normal,
		Body,
		Foot,
		Sensor,
		Attack,
		Heal,
		Null,		// 当たり判定をチェックしない
	};
	struct AddCollisionAABBData
	{
		Vector3 position;
		Vector3 size;
		CollisionType type;
	};
