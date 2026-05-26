<?xml version="1.0"?><doc>
<members>
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
<member name="M:SceneBase.StartFadeOut" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Scene\SceneBase.cpp" line="76">
フェードアウト開始
</member>
</members>
</doc>