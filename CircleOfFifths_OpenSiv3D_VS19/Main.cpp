# include <Siv3D.hpp> // OpenSiv3D v0.4.3

//http://www.ohshiro.tuis.ac.jp/~ohshiro/prog/game07_call_by_reference_pointer.html
Point Rotation2D(Point target, Point rotationCenter, double angle)
{
	double PI = 3.14159265358979323846;
	double theta = (angle / -180.0) * PI;
	target.y = -target.y; rotationCenter.y = -rotationCenter.y; // 数学座標と同じ様にするためにy座標値を反転

	Point pos;
	pos.x = (target.x - rotationCenter.x) * cos(theta) - (target.y - rotationCenter.y) * sin(theta) + rotationCenter.x;
	pos.y = -1.0 * ((target.x - rotationCenter.x) * sin(theta) + (target.y - rotationCenter.y) * cos(theta) + rotationCenter.y);
	return pos;
}

void Main()
{
	const Font majorNoteFont(40, Typeface::Bold);
	const Font minorNoteFont(15, Typeface::Bold);
	const Font majorNoteFontS(30, Typeface::Bold);
	const Font minorNoteFontS(12, Typeface::Bold);
	const Font majorDegreeFont(15, Typeface::Bold);
	const Font minorDegreeFont(10, Typeface::Bold);
	const Font infoFont(25);
	const Font infoFontS(15);

	const String majorNoteNames[] = { U"C",U"F",U"B♭",U"E♭" ,U"A♭" ,U"D♭\nC♯" ,U"F♯\nG♭" ,U" B\nC♭" ,U"E" ,U"A" ,U"D",U"G" };
	const String minorNoteNames[] = { U"Am",U"Dm",U"Gm",U"Cm" ,U"Fm" ,U"B♭m\nA♯m" ,U"D♯m\nE♭m" ,U"G♯m\nA♭m" ,U"C♯m" ,U"F♯m" ,U"Bm",U"Em" };
	const String majorDegreeNames[] = { U"I",U"IV",U"VII♭",U"III♭" ,U"VI♭" ,U"II♭ I♯" ,U"IV♯ V♭" ,U" VII I♭" ,U"III" ,U"VI" ,U"II",U"V" };
	const String minorDegreeNames[] = { U"VIm",U"IIm",U"Vm",U"Im" ,U"IVm" ,U"VII♭m\nVI♯m" ,U"II♯m\nIII♭m" ,U"V♯m\nVI♭m" ,U"I♯m" ,U"IV♯m" ,U"VIIm",U"IIIm" };

	const ColorF backgroundColor(U"#454545");
	const ColorF foregroundColor(U"#e9e9e9");
	const ColorF backgroundColorAlpha(U"#45454580");
	const ColorF foregroundColorAlpha(U"#e9e9e980");

	const ColorF majorBackgroundColors[] = {
		ColorF(U"#dadada"), ColorF(U"#cacaca"), ColorF(U"#aea29e"),
		ColorF(U"#9a8b85"), ColorF(U"#aea29e"), ColorF(U"#2954c1"),
		ColorF(U"#ff6633"), ColorF(U"#f1ab31"), ColorF(U"#f2ba5a"),
		ColorF(U"#f1ab31"), ColorF(U"#f2ba5a"), ColorF(U"#cacaca")
	};
	const ColorF minorBackgroundColors[] = {
		ColorF(U"#dadada"), ColorF(U"#cacaca"), ColorF(U"#aea29e"),
		ColorF(U"#9a8b85"), ColorF(U"#aea29e"), ColorF(U"#6641a2"),
		ColorF(U"#7a46c5"), ColorF(U"#6641a2"), ColorF(U"#15e7ac"),
		ColorF(U"#12f3b4"), ColorF(U"#15e7ac"), ColorF(U"#cacaca")
	};

	Window::SetTitle(U"五度圏");
	Window::Resize(800, 800);
	Scene::SetBackground(backgroundColor);

	const int centerCircleRadius = 20;
	const int mainCircleRadius = 300 + centerCircleRadius;
	const int mainCirclePosX = Window::ClientWidth() / 2;
	const int mainCirclePosY = Window::ClientHeight() / 2;

	const int pieStartDeg = 345;
	const int pieOffsetDeg = 30;
	int pieRotateOffsetDeg = 0;

	while(System::Update())
	{
		ClearPrint();

		Circle majorCircle(mainCirclePosX, mainCirclePosY, mainCircleRadius);
		Circle minorCircle(mainCirclePosX, mainCirclePosY, mainCircleRadius / 2);
		Circle centerCircle(mainCirclePosX, mainCirclePosY, centerCircleRadius);

		for(size_t i = 0; i < 12; i++)
		{
			majorCircle.drawPie(ToRadians(pieStartDeg + pieOffsetDeg * i), ToRadians(pieOffsetDeg), majorBackgroundColors[i]);
			minorCircle.drawPie(ToRadians(pieStartDeg + pieOffsetDeg * i), ToRadians(pieOffsetDeg), minorBackgroundColors[i]);
		}

		//中心円を描画
		centerCircle.draw(backgroundColor);

		//枠線を描画
		centerCircle.drawFrame(0, 85, foregroundColorAlpha);
		centerCircle.drawFrame(0, 40, foregroundColor);
		centerCircle.drawFrame(2, 34, backgroundColor);
		majorCircle.drawFrame(3, 3, foregroundColor);
		minorCircle.drawFrame(3, 3, foregroundColor);
		majorCircle.drawFrame(50, 0, foregroundColorAlpha);

		//音名を描画
		for(int i = 0; i < std::end(majorNoteNames) - std::begin(majorNoteNames); i++)
		{
			majorDegreeFont(majorDegreeNames[i]).drawAt(Rotation2D(Point(mainCirclePosX, mainCirclePosY - mainCircleRadius + mainCircleRadius / 4 - 55), Point(mainCirclePosX, mainCirclePosY), pieOffsetDeg * i), Palette::Black);
			minorDegreeFont(minorDegreeNames[i]).drawAt(Rotation2D(Point(mainCirclePosX, mainCirclePosY - mainCircleRadius / 2 + mainCircleRadius / 6 + 25), Point(mainCirclePosX, mainCirclePosY), pieOffsetDeg * i), Palette::Black);

			if(i == 5 || i == 6 || i == 7)
			{
				majorNoteFontS(majorNoteNames[i]).drawAt(Rotation2D(Point(mainCirclePosX, mainCirclePosY - mainCircleRadius + mainCircleRadius / 4 + 25), Point(mainCirclePosX, mainCirclePosY), (pieOffsetDeg * i) + pieRotateOffsetDeg), Palette::Black);
				minorNoteFontS(minorNoteNames[i]).drawAt(Rotation2D(Point(mainCirclePosX, mainCirclePosY - mainCircleRadius / 2 + mainCircleRadius / 6 - 22), Point(mainCirclePosX, mainCirclePosY), (pieOffsetDeg * i) + pieRotateOffsetDeg), Palette::Black);
			}
			else
			{
				majorNoteFont(majorNoteNames[i]).drawAt(Rotation2D(Point(mainCirclePosX, mainCirclePosY - mainCircleRadius + mainCircleRadius / 4 + 25), Point(mainCirclePosX, mainCirclePosY), (pieOffsetDeg * i) + pieRotateOffsetDeg), Palette::Black);
				minorNoteFont(minorNoteNames[i]).drawAt(Rotation2D(Point(mainCirclePosX, mainCirclePosY - mainCircleRadius / 2 + mainCircleRadius / 6 - 22), Point(mainCirclePosX, mainCirclePosY), (pieOffsetDeg * i) + pieRotateOffsetDeg), Palette::Black);
			}
		}

		//解説を描画
		infoFont(U"基調和音").drawAt(mainCirclePosX, mainCirclePosY - mainCircleRadius - 40, ColorF(U"#cacaca"));
		infoFont(U"トライトーン代理").drawAt(mainCirclePosX, mainCirclePosY + mainCircleRadius + 30, ColorF(U"#ff6633"));
		infoFontS(U"ダブル・ミクスチュア").drawAt(mainCirclePosX, mainCirclePosY + mainCircleRadius + 60, ColorF(U"#9f74dc"));
		infoFont(U"裏コード").drawAt(mainCirclePosX + 180, mainCirclePosY + mainCircleRadius + 10, ColorF(U"#5379d8"));
		infoFont(U"パ\nラ\nレ\nル\nマ\nイ\nナ\n丨").drawAt(mainCirclePosX + mainCircleRadius + 40, mainCirclePosY, ColorF(U"#aea29e"));
		infoFont(U"二\n次\nド\nミ\nナ\nン\nト").drawAt(mainCirclePosX - mainCircleRadius - 30, mainCirclePosY, ColorF(U"#f1ab31"));
		infoFontS(U"パ\nラ\nレ\nル\nメ\nジ\nャ\n丨").drawAt(mainCirclePosX - mainCircleRadius - 60, mainCirclePosY, ColorF(U"#15e7ac"));

		//キーボード処理
		if(KeyRight.down())
		{
			pieRotateOffsetDeg = pieRotateOffsetDeg + pieOffsetDeg;
		}
		if(KeyLeft.down())
		{
			pieRotateOffsetDeg = pieRotateOffsetDeg - pieOffsetDeg;
		}
	}
}

//
// = アドバイス =
// Debug ビルドではプログラムの最適化がオフになります。
// 実行速度が遅いと感じた場合は Release ビルドを試しましょう。
// アプリをリリースするときにも、Release ビルドにするのを忘れないように！
//
// 思ったように動作しない場合は「デバッグの開始」でプログラムを実行すると、
// 出力ウィンドウに詳細なログが表示されるので、エラーの原因を見つけやすくなります。
//
// = お役立ちリンク =
//
// OpenSiv3D リファレンス
// https://siv3d.github.io/ja-jp/
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/basic/
//
// よくある間違い
// https://siv3d.github.io/ja-jp/articles/mistakes/
//
// サポートについて
// https://siv3d.github.io/ja-jp/support/support/
//
// Siv3D ユーザコミュニティ Slack への参加
// https://siv3d.github.io/ja-jp/community/community/
//
// 新機能の提案やバグの報告
// https://github.com/Siv3D/OpenSiv3D/issues
//