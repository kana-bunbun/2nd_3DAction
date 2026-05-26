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
<member name="T:Status.Player" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\Animation.h" line="5">
<summary>
プレイヤーのアニメーションID
ここの名前はある程度自分でわかりやすい名前にしてもいい
</summary>
</member>
<member name="T:Status.Bee" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\Animation.h" line="19">
<summary>
蜂のアニメーションID
</summary>
</member>
<member name="T:Status.AnimData" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\Animation.h" line="33">
<summary>
アニメーションのデータ
</summary>
</member>
<member name="M:AnimatioController.Init(System.Int32)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\AnimatioController.h" line="11">
<summary>
初期化処理
</summary>
</member>
<member name="M:AnimatioController.PlayAnimation(Status.AnimData!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\AnimatioController.h" line="16">
<summary>
アニメーションを再生する関数
</summary>
<param name="data">アニメーションのデータ</param>
</member>
<member name="M:AnimatioController.ResetPlayCount" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\AnimatioController.h" line="21">
<summary>
アニメーションの再生カウントをリセットする関数
</summary>
</member>
<member name="M:AnimatioController.Update" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\AnimatioController.h" line="25">
<summary>
更新処理
</summary>
</member>
<member name="M:AnimatioController.IsPlaying" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\AnimatioController.h" line="30">
<summary>
アニメーションを再生しているかどうかを返す関数
</summary>
<returns>再生中ならtrue</returns>
</member>
<member name="M:AnimatioController.Debug" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\AnimatioController.h" line="36">
<summary>
デバッグ表示
</summary>
</member>
<member name="M:AnimatioController.GetPlayCount" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\AnimatioController.h" line="41">
<summary>
アニメーションの再生カウントを取得する関数
</summary>
<returns></returns>
</member>
<member name="M:AnimatioController.CheckOverMoment(System.Single)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\AnimatioController.h" line="46">
<summary>
指定した時間を過ぎた瞬間かどうか
</summary>
<param name="time">指定した時間</param>
<returns>過ぎた瞬間true</returns>
</member>
<member name="M:AnimatioController.SetAnimSpeed(System.Single)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\AnimatioController.h" line="52">
<summary>
アニメーションの才瀬尾速度を設定する関数
</summary>
<param name="speed">アニメーションの速さ(割合)</param>
</member>
<member name="M:AnimatioController.IsForcePlay" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\AnimatioController.h" line="58">
<summary>
割り込み不可能かどうかを取得する関数
</summary>
<returns>割り込み不可能の時true</returns>
</member>
<member name="M:Player.#ctor" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\Player.h" line="9">
<summary>
繝励Ξ繧､繝､繝ｼ縺ｮ繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ
</summary>
</member>
<member name="M:Player.Dispose" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\Player.h" line="13">
<summary>
繝励Ξ繧､繝､繝ｼ縺ｮ繝・せ繝医Λ繧ｯ繧ｿ
</summary>
</member>
<member name="M:Player.Init" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\Player.h" line="17">
<summary>
蛻晄悄蛹門・逅・
</summary>
</member>
<member name="M:Player.SetCamera(Camera*)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\Player.h" line="23">
<summary>
繧ｫ繝｡繝ｩ縺ｮ繝昴う繝ｳ繧ｿ繧呈ｸ｡縺咎未謨ｰ
</summary>
<param name="camera"></param>
</member>
<member name="F:Player.m_animation" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\Player.h" line="29">
<summary>
繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ邂｡逅・ｒ陦後≧
</summary>
</member>
<member name="F:Player.m_animData" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\Player.h" line="33">
<summary>
繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ繝・・繧ｿ縺ｮ驟榊・
</summary>
</member>
<member name="F:Player.m_status" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\Player.h" line="37">
<summary>
迴ｾ蝨ｨ縺ｮ繧ｹ繝・・繧ｿ繧ｹ
</summary>
</member>
<member name="F:Player.m_pCamera" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\Player.h" line="41">
<summary>
繧ｫ繝｡繝ｩ縺ｮ繝昴う繝ｳ繧ｿ
</summary>
</member>
<member name="F:Player.m_animHandle" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\Player.h" line="45">
<summary>
繧｢繝九Γ繝ｼ繧ｷ繝ｧ繝ｳ縺ｮ繝上Φ繝峨Ν
</summary>
</member>
<member name="F:Player.m_desireRad" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\World\Character\Player.h" line="50">
<summary>
繝励Ξ繧､繝､繝ｼ縺ｮ隗貞ｺｦ
</summary>
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
<member name="T:Camera" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="8">
<summary>
カメラのクラス
</summary>
</member>
<member name="M:Camera.Init(Player*)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="19">
<summary>
初期設定
</summary>
</member>
<member name="M:Camera.End" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="24">
<summary>
後処理
</summary>
</member>
<member name="M:Camera.Update" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="29">
<summary>
更新処理
</summary>
</member>
<member name="M:Camera.Draw" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="34">
<summary>
描画
</summary>
</member>
<member name="M:Camera.GetHRadian" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="39">
<summary>
カメラの水平アングルを取得する
</summary>
<returns>カメラの水平アングル</returns>
</member>
<member name="M:Camera.SetPad(Pad.Player!System.Runtime.CompilerServices.IsConst)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="45">
<summary>
コントローラーを割り当てる
</summary>
<param name="padNum">コントローラーの番号</param>
<returns></returns>
</member>
<member name="M:Camera.GetYawRadian" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="51">
<summary>
カメラの水平方向(ヨー)のラジアン角を取得する関数
</summary>
<returns>カメラの水平方向(ヨー)のラジアン角</returns>
</member>
<member name="M:Camera.SetTarget(Transform!System.Runtime.CompilerServices.IsConst*!System.Runtime.CompilerServices.IsImplicitlyDereferenced)" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="56">
<summary>
カメラが追従するターゲットを設定
</summary>
<param name="transform">追従するターゲットのTransform</param>
<returns></returns>
</member>
<member name="M:Camera.UpdateDistance" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="67">
<summary>
被写体との距離を更新
</summary>
</member>
<member name="M:Camera.UpdateAngleInput" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="72">
<summary>
入力に基づいたカメラの角度を更新
</summary>
</member>
<member name="M:Camera.UpdateAngleLerp" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="76">
<summary>
補間での角度の更新処理
</summary>
</member>
<member name="M:Camera.UpdateCameraPos" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="80">
<summary>
 カメラの角度から位置を計算して更新
</summary>
</member>
<member name="F:Camera.m_transform" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="107">
<summary>
自身の座標・回転・拡縮
</summary>
</member>
<member name="F:Camera.m_currentDistance" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="112">
<summary>
現在のカメラの被写体までの距離
</summary>
</member>
<member name="F:Camera.m_desireDistance" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="116">
<summary>
補間する際の目標となる距離
</summary>
</member>
<member name="F:Camera.m_lerpDistance" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="120">
<summary>
距離の補間の割合
</summary>
</member>
<member name="F:Camera.m_pPlayer" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="125">
<summary>
プレイヤーのポインタ
</summary>
</member>
<member name="F:Camera.m_pad" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="131">
<summary>
自身を操作するコントローラー
</summary>
</member>
<member name="F:Camera.m_input" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\Camera\Camera.h" line="135">
<summary>
入力に基づいた角度の更新処理をするかどうかのフラグ
</summary>
</member>
</members>
</doc>