<?xml version="1.0"?><doc>
<members>
<member name="T:SceneManager" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneManager.h" line="6">
<summary>
ゲームシーン全体を管理するクラス
</summary>
</member>
<member name="M:SceneManager.#ctor" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneManager.h" line="13">
<summary>
コンストラクタ
メンバの初期設定
</summary>
</member>
<member name="M:SceneManager.Dispose" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneManager.h" line="19">
<summary>
デストラクタ
メンバの後処理
</summary>
</member>
<member name="M:SceneManager.Init" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneManager.h" line="25">
<summary>
メンバの設定
</summary>
</member>
<member name="M:SceneManager.End" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneManager.h" line="30">
<summary>
メンバの破棄
</summary>
</member>
<member name="M:SceneManager.Update" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneManager.h" line="35">
<summary>
毎フレームの処理
</summary>
</member>
<member name="M:SceneManager.Draw" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneManager.h" line="40">
<summary>
シーンの描画
</summary>
</member>
<member name="T:SceneBase" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneBase.h" line="3">
<summary>
各画面の基本クラス
基本的にはこのクラスを継承して各画面のクラスを作成する
作成したクラスをSceneManagerクラスから呼び出すことで保守しやすくする
</summary>
</member>
<member name="M:SceneBase.#ctor" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneBase.h" line="12">
<summary>
コンストラクタ
メンバ変数の初期設定
</summary>
</member>
<member name="M:SceneBase.Dispose" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneBase.h" line="18">
<summary>
デストラクタ
派生クラスを破棄した時に備えて仮想デストラクタ化
</summary>
</member>
<member name="M:SceneBase.Init" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneBase.h" line="24">
<summary>
初期設定
具体的な処理は各画面毎で異なるので純粋仮想関数にして派生先で実装
</summary>
</member>
<member name="M:SceneBase.End" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneBase.h" line="30">
<summary>
終了処理
具体的な処理は各画面毎で異なるので純粋仮想関数にして派生先で実装
</summary>
</member>
<member name="M:SceneBase.Update" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneBase.h" line="36">
<summary>
更新処理
</summary>
<returns>自身のポインタを返す</returns>
</member>
<member name="M:SceneBase.Draw" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneBase.h" line="42">
<summary>
描画処理
具体的な処理は各画面毎で異なるので純粋仮想関数にして派生先で実装
</summary>
</member>
<member name="M:SceneBase.UpdateFade" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneBase.h" line="52">
<summary>
フェードの更新
</summary>
</member>
<member name="M:SceneBase.DrawFade" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneBase.h" line="57">
<summary>
フェードの描画
</summary>
</member>
<member name="M:SceneBase.IsFadingIn" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneBase.h" line="62">
<summary>
フェードイン中かどうかを判定
</summary>
<returns>フェードイン中ならtrue</returns>
</member>
<member name="M:SceneBase.IsFadingOut" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneBase.h" line="68">
<summary>
フェードアウト中かどうかを判定
</summary>
<returns>フェードアウト中ならtrue</returns>
</member>
<member name="M:SceneBase.IsFading" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneBase.h" line="74">
<summary>
フェード中かどうかを判定
</summary>
<returns>フェード中ならtrue</returns>
</member>
<member name="M:SceneBase.StartFadeOut" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneBase.h" line="80">
<summary>
フェードアウト開始
</summary>
</member>
<member name="T:Vector3" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Vector3.h" line="3">
<summary>
3次元ベクトル構造体
基本的には値として使うことが多いので構造体で作成する
→publicで作っていくが、気になればprivateを使い分ける
処理が膨大になってきたらクラスに変更すればよい
</summary>
</member>
<member name="F:Vector3.x" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Vector3.h" line="12">
<summary>
各軸の座標
</summary>
</member>
<member name="F:Vector3.zero" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Vector3.h" line="21">
<summary>
ゼロベクトル
</summary>
</member>
<member name="F:Vector3.XAxis" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Vector3.h" line="26">
<summary>
X軸の正方向の単位ベクトル
</summary>
</member>
<member name="F:Vector3.YAxis" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Vector3.h" line="31">
<summary>
Y軸の正方向の単位ベクトル
</summary>
</member>
<member name="F:Vector3.ZAxis" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Vector3.h" line="36">
<summary>
Z軸の正方向の単位ベクトル
</summary>
</member>
<member name="M:Vector3.#ctor" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Vector3.h" line="42">
<summary>
デフォルトコンストラクタ
定数宣言の際にも使用できるよう consterxpr をつけて宣言
</summary>
</member>
<member name="M:Vector3.#ctor(System.Single,System.Single,System.Single)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Vector3.h" line="47">
<summary>
引数ありのコンストラクタ
定数宣言の際にも使用できるよう consterxpr をつけて宣言
</summary>
<param name="x">x方向の値</param>
<param name="y">y方向の値</param>
<param name="z">z方向の値</param>
</member>
<member name="M:Vector3.ToVECTOR" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Vector3.h" line="73">
<summary>
DxLibのVECTOR型に変換する関数
</summary>
<returns></returns>
</member>
<member name="M:Input.Update" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Input.h" line="47">
入力情報の取得・更新
ゲームループで呼ぶ
</member>
<member name="M:Input.IsDown(Input.Button,Pad.Player!System.Runtime.CompilerServices.IsConst)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Input.h" line="51">
<summary>
キーが押されているかどうかを調べる
</summary>
<param name="key">入力されたキー</param>
<returns>入力結果 押されていたらtrue</returns>
</member>
<member name="M:Input.IsPressed(Input.Button,Pad.Player!System.Runtime.CompilerServices.IsConst)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Input.h" line="58">
<summary>
キーが押されているかどうかを調べる
</summary>
<param name="key">入力されたキー</param>
<returns>入力結果 押された瞬間だったらtrue</returns>
</member>
<member name="M:Input.IsReleased(Input.Button,Pad.Player!System.Runtime.CompilerServices.IsConst)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Input.h" line="65">
<summary>
キーが押されているかどうかを調べる
</summary>
<param name="key">入力されたキー</param>
<returns>入力結果 離された瞬間だったらtrue</returns>
</member>
<member name="M:Input.Hold(Input.Button,Pad.Player!System.Runtime.CompilerServices.IsConst)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Input.h" line="72">
<summary>
キーが長押しされているかどうか調べる
</summary>
<param name="key">入力されたキー</param>
<returns>入力結果 長押しされていたらtrue</returns>
</member>
<member name="M:Input.AnalogAngle(Input.Joystick!System.Runtime.CompilerServices.IsConst,Pad.Player!System.Runtime.CompilerServices.IsConst)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Input.h" line="79">
<summary>
アナログレバーの入力角度を調べる
</summary>
<returns>入力角度のデグリー角</returns>
</member>
<member name="M:Input.PadAnalogAmount(Input.Joystick!System.Runtime.CompilerServices.IsConst,Pad.Player!System.Runtime.CompilerServices.IsConst)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Input.h" line="84">
<summary>
アナログレバーの入力量を調べる
</summary>
<returns>レバーをどれだけ倒しているか,0～1</returns>
</member>
<member name="M:Input.Debug" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\Input.h" line="90">
<summary>
デバッグ処理
</summary>
</member>
<member name="T:Collision.Type" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="9">
<summary>
形状データ
</summary>
</member>
<member name="F:Collision.Result.isHit" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="20">
<summary>
衝突したかどうか
</summary>
</member>
<member name="F:Collision.Result.normal" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="24">
<summary>
衝突した面の法線ベクトル
</summary>
</member>
<member name="F:Collision.Result.penetration" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="28">
<summary>
めり込み具合
どれだぇ押し返すのかに使用したりする
</summary>
</member>
<member name="T:Collision.Shape" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="36">
<summary>
衝突判定の形状の抽象クラス
これを継承し様々な形状で対応できるようにする
</summary>
</member>
<member name="M:Collision.Shape.GetType" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="43">
<summary>
形状データを取得する
</summary>
<returns></returns>
</member>
<member name="M:Collision.Shape.CheckCollision(Collision.Shape!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="48">
<summary>
衝突判定
</summary>
<returns></returns>
</member>
<member name="M:Collision.Shape.SetPosition(Vector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="53">
<summary>
座標を更新
</summary>
<param name="pos"></param>
</member>
<member name="M:Collision.Shape.GetPos" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="58">
<summary>
座標の取得
</summary>
<returns></returns>
</member>
<member name="M:Collision.Shape.DebugDraw" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="63">
<summary>
形状のデバッグ描画
</summary>
</member>
<member name="M:Collision.Sphere.GetType" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="74">
<summary>
形状データを取得する
</summary>
<returns></returns>
</member>
<member name="M:Collision.Sphere.CheckCollision(Collision.Shape!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="79">
<summary>
衝突判定
</summary>
<returns></returns>
</member>
<member name="M:Collision.Sphere.SetPosition(Vector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="84">
<summary>
座標を更新
</summary>
<param name="pos"></param>
</member>
<member name="M:Collision.Sphere.GetPos" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="89">
<summary>
座標の取得
</summary>
<returns></returns>
</member>
<member name="M:Collision.Sphere.GetRadus" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="94">
<summary>
半径の取得
</summary>
<returns></returns>
</member>
<member name="M:Collision.Sphere.DebugDraw" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="99">
<summary>
形状のデバッグ描画
</summary>
</member>
<member name="F:Collision.Sphere.m_center" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="104">
<summary>
球の中心座標
</summary>
</member>
<member name="F:Collision.Sphere.m_radius" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="108">
<summary>
球の半径
</summary>
</member>
<member name="M:Collision.AABB.GetType" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="118">
<summary>
形状データを取得する
</summary>
<returns></returns>
</member>
<member name="M:Collision.AABB.CheckCollision(Collision.Shape!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="123">
<summary>
衝突判定
</summary>
<returns></returns>
</member>
<member name="M:Collision.AABB.SetPosition(Vector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="128">
<summary>
座標を更新
</summary>
<param name="pos"></param>
</member>
<member name="M:Collision.AABB.GetPos" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="133">
<summary>
座標の取得
</summary>
<returns></returns>
</member>
<member name="M:Collision.AABB.DebugDraw" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="138">
<summary>
形状のデバッグ描画
</summary>
</member>
<member name="M:Collision.CheckPointInAABB(Collision.AABB*!System.Runtime.CompilerServices.IsImplicitlyDereferenced,Vector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Collision.h" line="149">
<summary>
点がAABB内に入っているかどうかを調べる
</summary>
<param name="pos"></param>
<returns></returns>
</member>
<member name="T:SceneTest" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneTest.h" line="32">
<summary>
授業で作成して確認用のクラス
なにか機能の確認を行うときにこのクラスで検証をする
</summary>
</member>
<member name="M:SceneTest.#ctor" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneTest.h" line="40">
<summary>
SceneTest画面のコンストラクタ
メンバの初期設定を行う
</summary>
</member>
<member name="M:SceneTest.Dispose" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneTest.h" line="46">
<summary>
SceneTest画面のデストラクタ
メンバの後処理を行う
</summary>
</member>
<member name="M:SceneTest.Init" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneTest.h" line="52">
<summary>
画面の初期設定を行う
</summary>
</member>
<member name="M:SceneTest.End" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneTest.h" line="57">
<summary>
画面の後処理を行う
</summary>
</member>
<member name="M:SceneTest.Update" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneTest.h" line="62">
<summary>
SceneTest画面の処理を行う
</summary>
<returns>SceneBase型のポインタ 次に処理をする画面</returns>
</member>
<member name="M:SceneTest.Draw" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneTest.h" line="68">
<summary>
SceneTest画面の描画を行う
</summary>
</member>
<member name="M:SceneTest.DrawGround" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneTest.h" line="75">
<summary>
位置関係が分かるように地面を線で描画する
</summary>
</member>
<member name="F:SceneTest.m_pCamera" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneTest.h" line="82">
<summary>
Cameraクラスのポインタ
</summary>
</member>
<member name="F:SceneTest.m_playerNum" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneTest.h" line="88">
<summary>
プレイヤーの数
</summary>
</member>
<member name="F:SceneTest.m_pBee" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneTest.h" line="93">
<summary>
Beeのポインタ
</summary>
</member>
</members>
</doc>