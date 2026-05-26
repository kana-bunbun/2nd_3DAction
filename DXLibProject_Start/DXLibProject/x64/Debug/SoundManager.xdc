<?xml version="1.0"?><doc>
<members>
<member name="T:Sound.BGM" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\System\SoundManager.h" line="8">
<summary>
BGMのIDラベル
</summary>
</member>
<member name="T:Sound.SE" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\System\SoundManager.h" line="18">
<summary>
SEのIDラベル
</summary>
</member>
<member name="T:SoundManager" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\System\SoundManager.h" line="32">
<summary>
SEやBGMの読み込み、再生、停止等を管理するクラス
</summary>
</member>
<member name="M:SoundManager.GetInstance" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\System\SoundManager.h" line="40">
<summary>
シングルトンのインスタンスを取得
</summary>
<returns></returns>
</member>
<member name="M:SoundManager.LoadSe" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\System\SoundManager.h" line="48">
<summary>
SEの読み込み
</summary>
</member>
<member name="M:SoundManager.PlaySe(Sound.SE)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\System\SoundManager.h" line="53">
<summary>
SEの再生
</summary>
<param name="id">再生したいSEのID</param>
</member>
<member name="M:SoundManager.LoadBGM" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\System\SoundManager.h" line="59">
<summary>
BGMの読み込み
</summary>
</member>
<member name="M:SoundManager.PlayBGM(Sound.BGM)" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\System\SoundManager.h" line="64">
<summary>
BGMの再生
</summary>
<param name="id">再生したいBGMのID</param>
</member>
<member name="M:SoundManager.StopBGM" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\System\SoundManager.h" line="70">
<summary>
再生中のBGMの停止
</summary>
</member>
<member name="M:SoundManager.Release" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\System\SoundManager.h" line="75">
<summary>
読み込んだデータの解放
</summary>
</member>
<member name="M:SoundManager.#ctor" decl="true" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\System\SoundManager.h" line="82">
<summary>
コンストラクタ
シングルトンパターンのクラスならprivteにして生成できないようにする
</summary>
</member>
<member name="F:SoundManager.m_seHandles" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\System\SoundManager.h" line="100">
<summary>
SEのハンドル
</summary>
</member>
<member name="F:SoundManager.m_bgmHandles" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\System\SoundManager.h" line="105">
<summary>
BGMのハンドル
</summary>
</member>
<member name="F:SoundManager.m_currentBgmHandle" decl="false" source="C:\Users\student1\Desktop\2nd_3DAction\DXLibProject_Start\System\SoundManager.h" line="110">
<summary>
再生中のBGMハンドル
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