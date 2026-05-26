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
<member name="T:Transform" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Transform.h" line="5">
<summary>
座標・回転・拡縮を管理する構造体
</summary>
</member>
<member name="F:Transform.position" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Transform.h" line="11">
<summary>
座標(ワールド座標)
</summary>
</member>
<member name="F:Transform.rotation" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Transform.h" line="16">
<summary>
回転(ラジアン角)
三角関数との親和性を考慮し、ラジアン角で扱う
</summary>
</member>
<member name="F:Transform.scale" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Transform.h" line="22">
<summary>
拡大率(1.0で等倍)
</summary>
</member>
<member name="M:Transform.Translate(Vector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Transform.h" line="27">
<summary>
座標の移動
</summary>
<param name="vec">移動成分のベクトル</param>
</member>
<member name="M:Transform.RotateRad(Vector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Transform.h" line="32">
<summary>
回転(ラジアン角)
</summary>
<param name="vec">回転成分のベクトル</param>
</member>
<member name="M:Transform.RotateDeg(Vector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Transform.h" line="37">
<summary>
回転(デグリー角で指定)
</summary>
<param name="vec">回転成分のベクトル</param>
</member>
<member name="M:Transform.SetRotateDeg(Vector3!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Transform.h" line="42">
<summary>
角度を指定(デグリー角で指定)
</summary>
<param name="vecDeg">回転成分のベクトル</param>
</member>
<member name="M:Transform.VetRotateDeg" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Transform.h" line="47">
<summary>
回転の値をデグリー角で取得する関数
</summary>
<returns>デグリー角の回転成分</returns>
</member>
<member name="M:Transform.Reset" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Component\Transform.h" line="52">
<summary>
各値の初期化
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
<member name="T:GameObject" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\GameObject.h" line="6">
<summary>
繧ｲ繝ｼ繝縺ｧ謇ｱ縺・が繝悶ず繧ｧ繧ｯ繝医・蝓ｺ譛ｬ繧ｯ繝ｩ繧ｹ
蠎ｧ讓吶・繝｢繝・Ν繝ｻ陦晉ｪ∝愛螳壹・繝ｩ繧､繝輔し繧､繧ｯ繝ｫ繧堤ｮ｡逅・☆繧・
繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繧呈戟縺｣縺溘が繝悶ず繧ｧ繧ｯ繝医ｒ菴懊ｋ髫帙・縲∝挨騾泌ｯｾ蠢懊′蠢・ｦ・
</summary>
</member>
<member name="M:GameObject.Init" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\GameObject.h" line="17">
<summary>
繝・せ繝医Λ繧ｯ繧ｿ繝ｻ繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ縺ｨInit髢｢謨ｰ縲・nd髢｢謨ｰ繧貞玄蛻･
Init繝ｻEnd髢｢謨ｰ縺ｯ繧ｲ繝ｼ繝逧・↑邨ゆｺ・・髢句ｧ句・逅・
繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ繝ｻ繝・せ繝医Λ繧ｯ繧ｿ縺ｯC++繧ｪ繝悶ず繧ｧ繧ｯ繝医→縺励※縺ｮ蠕悟・逅・ｭ峨ｒ縺吶ｋ髫・
Init繝ｻEnd髢｢謨ｰ縺ｯ繝槭ロ繝ｼ繧ｸ繝｣繝ｼ邨檎罰遲峨〒蜻ｼ縺ｶ
繝｡繝ｳ繝舌・隗｣謾ｾ繧・ご繝ｼ繝菴ｿ逕ｨ荳翫・蠕悟・逅・〒陦後≧
繝・せ繝医Λ繧ｯ繧ｿ縺ｯ繝｡繝｢繝ｪ縺ｮ髢区叛縲√・繧､繝ｳ繧ｿ縺ｮ蠕悟・逅・∫ｴ譽・ｿ倥ｌ繧帝亟縺・
</summary>
</member>
<member name="M:GameObject.GetTransform" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\GameObject.h" line="31">
<summary>
繝医Λ繝ｳ繧ｹ繝輔か繝ｼ繝繧貞叙蠕・
</summary>
<returns></returns>
</member>
<member name="M:GameObject.GetPosition" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\GameObject.h" line="36">
<summary>
蠎ｧ讓吶ｒ蜿門ｾ・
</summary>
<returns></returns>
</member>
<member name="M:GameObject.GetCollision" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\GameObject.h" line="41">
<summary>
蠖薙◆繧雁愛螳壹・蜿門ｾ・
</summary>
<returns></returns>
</member>
<member name="M:GameObject.ResolveCollision(Collision.Result!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\GameObject.h" line="46">
<summary>
陦晉ｪ∝ｾ後・蜃ｦ逅・
</summary>
<param name="result"></param>
</member>
<member name="F:GameObject.m_transform" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\GameObject.h" line="52">
<summary>
蠎ｧ讓吶・蝗櫁ｻ｢繝ｻ諡｡邵ｮ
繧ｯ繝ｩ繧ｹ蜀・〒縺励°菴ｿ逕ｨ縺励↑縺・
GameObject繧ｯ繝ｩ繧ｹ縺ｮ繧､繝ｳ繧ｹ繧ｿ繝ｳ繧ｹ縺ｯ邨ｶ蟇ｾ縺ｫ謖√▲縺ｦ縺・ｋ諠・ｱ縺ｪ縺ｮ縺ｧ
蛟､繧ｪ繝悶ず繧ｧ繧ｯ繝医→縺励※螳｣險
</summary>
</member>
<member name="F:GameObject.m_modelHandle" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\GameObject.h" line="60">
<summary>
繝｢繝・Ν繝上Φ繝峨Ν
</summary>
</member>
<member name="F:GameObject.m_collision" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\GameObject.h" line="65">
<summary>
蠖薙◆繧雁愛螳・
繝昴Μ繝｢繝ｼ繝輔ぅ繧ｺ繝縺ｧ逡ｰ縺ｪ繧句ｽ｢迥ｶ繧偵け繝ｩ繧ｹ縺斐→縺ｫ謖√▽
nullptr縺ｫ縺励◆繧画戟縺溘↑縺・％縺ｨ繧る∈謚槭〒縺阪ｋ(遨肴･ｵ逧・↓縺ｯ菴ｿ逕ｨ縺励↑縺・
</summary>
</member>
</members>
</doc>