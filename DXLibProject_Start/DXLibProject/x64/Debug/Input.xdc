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
<member name="M:MyMath.NormalizeAngle(System.Single)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\MyMath.h" line="13">
<summary>
角度を-180度～180度までに収める関数
</summary>
<param name="angle">-180度～180度に収めたい値</param>
<returns>-180度～180度に収めた値</returns>
</member>
<member name="M:MyMath.NormalizeRadian(System.Single)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\MyMath.h" line="26">
<summary>
角度を-180度～180度までに収める関数
</summary>
<param name="angle">-180度～180度に収めたい値</param>
<returns>-180度～180度に収めた値</returns>
</member>
<member name="M:MyMath.Rate(System.Single,System.Single)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\MyMath.h" line="55">
<summary>
最大値からの割合を返す
</summary>
<param name="value">調べたい値</param>
<param name="Max">最大値</param>
<returns></returns>
</member>
<member name="M:MyMath.Sign(System.Single)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\MyMath.h" line="65">
<summary>
1か-1に変換して返す関数
</summary>
<param name="value">変換したい値</param>
<returns>値が正なら1、負なら-1を返す</returns>
</member>
<member name="M:MyMath.Distance(Vector3,Vector3)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Utility\MyMath.h" line="75">
<summary>
二点間の座標の差から距離を計算する関数
</summary>
<param name="pos1">1つ目の座標</param>
<param name="pos2">2つ目の座標</param>
<returns>2点間の距離</returns>
</member>
</members>
</doc>