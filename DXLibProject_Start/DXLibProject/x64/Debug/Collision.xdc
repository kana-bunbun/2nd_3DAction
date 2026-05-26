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