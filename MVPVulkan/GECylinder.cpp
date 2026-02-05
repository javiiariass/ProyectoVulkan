/**
 * @file GECylinder.cpp
 * @brief Implementación de la clase GECylinder.
 */

#include "GECylinder.h"

/**
 * @brief Crea la figura del cilindro.
 * @param p Número de divisiones en altura.
 * @param m Número de divisiones en circunferencia.
 * @param r Radio del cilindro.
 * @param l Longitud (altura) del cilindro.
 */
GECylinder::GECylinder(int p, int m, float r, float l)
{
	int numFaces = 2 * m * (p + 1);     ///< Número de caras
	int numVertices = (m + 1) * (p + 3);  ///< Número de vértices

	vertices.resize(numVertices);
	indices.resize(numFaces * 3);

	int verticesIndex = 0;
	int indicesIndex = 0;

	// ===== Casquete polar norte =====
	vertices[0] = { {0.0f, 0.0f, l },{0.0f, 0.0f, 1.0f } };
	verticesIndex++;

	for (int j = 0; j < m; j++)
	{
		float mCos = (float)cos(glm::radians(360.0f * j / m));
		float mSin = (float)sin(glm::radians(360.0f * j / m));
		vertices[verticesIndex] = { { mCos * r, mSin * r, l}, {0.0f, 0.0f, 1.0f} };
		verticesIndex++;

		indices[indicesIndex] = 0; ///< centro
		indices[indicesIndex + 1] = j + 1;
		indices[indicesIndex + 2] = (j + 2 > m ? 1 : j + 2);
		indicesIndex += 3;
	}

	// ===== Casquete polar sur =====
	vertices[verticesIndex] = { { 0.0f, 0.0f, -l},{0.0f, 0.0f, -1.0f } };
	verticesIndex++;

	for (int j = 0; j < m; j++)
	{
		float mCos = (float)cos(glm::radians(360.0f * j / m));
		float mSin = (float)sin(glm::radians(360.0f * j / m));
		vertices[verticesIndex] = { { mCos * r, -mSin * r, -l }, {0.0f, 0.0f, -1.0f} };
		verticesIndex++;

		indices[indicesIndex] = m + 1; ///< centro
		indices[indicesIndex + 1] = j + m + 2;
		indices[indicesIndex + 2] = (j + 2 > m ? m + 2 : j + m + 3);
		indicesIndex += 3;
	}


	// ===== Cuerpo =====
	for (int i = 0; i <= p; i++)
	{
		for (int j = 0; j <= m; j++)
		{
			float mCos = (float)cos(glm::radians(360.0f * j / m));
			float mSin = (float)sin(glm::radians(360.0f * j / m));
			vertices[verticesIndex] = { { mCos * r, mSin * r, l - 2 * l * i / p}, {mCos, mSin, 0.0f} };
			verticesIndex++;
		}
	}

	int base = 2 * m + 2;
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j < m; j++)
		{
			indices[indicesIndex] = base + (m + 1) * i + j;
			indices[indicesIndex + 1] = base + (m + 1) * (i + 1) + j;
			indices[indicesIndex + 2] = base + (m + 1) * (i + 1) + j + 1;
			indicesIndex += 3;

			indices[indicesIndex] = base + (m + 1) * i + j;
			indices[indicesIndex + 1] = base + (m + 1) * (i + 1) + j + 1;
			indices[indicesIndex + 2] = base + (m + 1) * i + j + 1;
			indicesIndex += 3;
		}
	}
}
