<?xml version="1.0"?><doc>
<members>
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
</members>
</doc>