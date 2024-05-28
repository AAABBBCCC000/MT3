#include <Novice.h>
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cmath>


const char kWindowTitle[] = "GC2C_14_リ_ブンタツ";

static const int kColumnWidth = 60;
static const int kRowHeight = 20;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	Novice::ScreenPrintf(x, y, label);
	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			Novice::ScreenPrintf(
			    x + column * kColumnWidth, y + row * kRowHeight + kRowHeight, "%6.02f",
			    matrix.m[row][column]);
		}
	}
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result = {};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = 0.0f;
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

Matrix4x4 MakeRotateXMatrix(float radian) {
	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	return {1.0f, 0.0f,      0.0f,     0.0f,
		    0.0f, cosTheta,  sinTheta, 0.0f,
	        0.0f, -sinTheta, cosTheta, 0.0f,
		    0.0f, 0.0f,      0.0f,     1.0f};
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	return {cosTheta, 0.0f, -sinTheta, 0.0f,
		    0.0f,     1.0f, 0.0f,      0.0f,
	        sinTheta, 0.0f, cosTheta,  0.0f,
		    0.0f,     0.0f, 0.0f,      1.0f};
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	float cosTheta = std::cos(radian);
	float sinTheta = std::sin(radian);
	return {cosTheta,  sinTheta, 0.0f, 0.0f,
	        -sinTheta, cosTheta, 0.0f, 0.0f,
	        0.0f,      0.0f,     1.0f, 0.0f,
	        0.0f,      0.0f,     0.0f, 1.0f};
	
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Vector3 rotate{0.4f, 1.43f, -0.8f};

		Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);

		Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);

		Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
		
		Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5, rotateYMatrix, "rotateYMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5 * 2, rotateZMatrix, "rotateZMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXYZMatrix");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
