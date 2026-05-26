<?xml version="1.0"?><doc>
<members>
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
<member name="T:GameSetting" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\GameSetting.h" line="3">
<summary>
ゲームの処理関連の初期設定を行う
</summary>
</member>
<member name="M:GameSetting.InitWindow" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\GameSetting.h" line="13">
<summary>
ウィンドウの初期設定
</summary>
</member>
<member name="M:GameSetting.InitDxLib3D" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\GameSetting.h" line="18">
<summary>
DXライブラリでの3D描画の設定
</summary>
</member>
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
<member name="T:MyRandom" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\MyRandom.h" line="3">
<summary>
乱数を生成するクラス
以下のページを参考に作成
</summary>
</member>
<member name="M:MyRandom.Init" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\MyRandom.h" line="10">
<summary>
疑似乱数の初期化(起動時に1回)
</summary>
</member>
<!-- メンバー 'M:MyRandom.Int(System.Int32,System.Int32)' に対して形式が正しくない XML ドキュメント コメントを破棄します。-->
<!-- メンバー 'M:MyRandom.Float(System.Single,System.Single)' に対して形式が正しくない XML ドキュメント コメントを破棄します。-->
<!-- メンバー 'M:MyRandom.Float01' に対して形式が正しくない XML ドキュメント コメントを破棄します。-->
<!-- メンバー 'M:MyRandom.Judge(System.Single)' に対して形式が正しくない XML ドキュメント コメントを破棄します。-->
</members>
</doc>