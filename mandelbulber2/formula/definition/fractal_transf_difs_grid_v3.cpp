/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * transfDIFSGridV2Iteration  fragmentarium code, mdifs by knighty (jan 2012)
 * and Buddhi
 */

#include "all_fractal_definitions.h"

cFractalTransfDIFSGridV3::cFractalTransfDIFSGridV3() : cAbstractFractal()
{
	nameInComboBox = "T>DIFS Grid V3";
	internalName = "transf_difs_grid_v3";
	internalID = fractal::transfDIFSGridV3;
	DEType = analyticDEType;
	DEFunctionType = customDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionCustomDE;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfDIFSGridV3::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 zc = z;
	
	{
		if (fractal->transformCommon.functionEnabledFalse)
		{
			for (int n = 0; n < fractal->transformCommon.int8X; n++)
			{
				CVector4 limit = fractal->transformCommon.additionConstant000;

				if (fractal->transformCommon.functionEnabledAx
						&& aux.i >= fractal->transformCommon.startIterationsA
						&& aux.i < fractal->transformCommon.stopIterationsA)
					zc.x = fabs(zc.x + limit.x) - fabs(zc.x - limit.x) - zc.x;

				if (fractal->transformCommon.functionEnabledAy
						&& aux.i >= fractal->transformCommon.startIterationsB
						&& aux.i < fractal->transformCommon.stopIterationsB)
					zc.y = fabs(zc.y + limit.y) - fabs(zc.y - limit.y) - zc.y;

				if (fractal->transformCommon.functionEnabledAzFalse
						&& aux.i >= fractal->transformCommon.startIterationsC
						&& aux.i < fractal->transformCommon.stopIterationsC)
					zc.z = fabs(zc.z + limit.z) - fabs(zc.z - limit.z) - zc.z;
			}
		}
	}
	


	if (fractal->transformCommon.functionEnabledMFalse)
	{
		zc.x += fractal->transformCommon.offsetA000.x;
		zc.x = fabs(z.x) - fractal->transformCommon.offsetA000.x;
	}

	if (fractal->transformCommon.functionEnabledNFalse)
	{
		zc.y += fractal->transformCommon.offsetA000.y;
		zc.y = fabs(z.y) - fractal->transformCommon.offsetA000.y;
	}

	if (fractal->transformCommon.functionEnabledAFalse)
		zc.x = zc.x + sign(zc.y) * .5 * fractal->transformCommon.intA;

	if (fractal->transformCommon.functionEnabledBFalse)
		zc.y = zc.y + sign(zc.x) * .5 * fractal->transformCommon.intB;

	if (fractal->transformCommon.functionEnabledCFalse) zc.x = max(fabs(zc.x), fabs(zc.y));

	if (fractal->transformCommon.functionEnabledDFalse) zc.x = sqrt((zc.x * zc.x) + (zc.y * zc.y));


	zc.z /= fractal->transformCommon.scaleF1;


	double tD = 1000.;

	if (fractal->transformCommon.functionEnabled) tD = zc.x - round(zc.x);

	tD = sqrt(tD * tD + zc.z * zc.z) - fractal->transformCommon.offset0;

	if (fractal->transformCommon.functionEnabledOFalse)
		tD = max(
			fabs(tD) - fractal->transformCommon.offsetA0, fabs(zc.z) - fractal->transformCommon.offsetB0);

	//tD = max((z.z)+ .003, tD);

	aux.dist = min(aux.dist, tD / (aux.DE + 1.0f));


	if (fractal->transformCommon.functionEnabledzFalse) z = zc;





	/*double size = fractal->transformCommon.scale1;
	double grid = 0.0;

	zc.z /= fractal->transformCommon.scaleF1;

	if (fractal->transformCommon.functionEnabledMFalse
			&& aux.i >= fractal->transformCommon.startIterationsM
			&& aux.i < fractal->transformCommon.stopIterationsM)
	{
		double temp = zc.x;
		zc.x = zc.x + sin(zc.y) * fractal->transformCommon.scaleA0;
		zc.y = zc.y + sin(temp) * fractal->transformCommon.scaleB0;
	}

	if (fractal->transformCommon.functionEnabledNFalse
			&& aux.i >= fractal->transformCommon.startIterationsN
			&& aux.i < fractal->transformCommon.stopIterationsN)
	{
		double k = fractal->transformCommon.angle0;

		if (fractal->transformCommon.functionEnabledAxFalse)
			k *= aux.i + fractal->transformCommon.offset1;

		double swap;
		if (!fractal->transformCommon.functionEnabledOFalse)
			swap = zc.x;
		else
			swap = zc.z;

		if (fractal->transformCommon.functionEnabledAzFalse) swap = fabs(swap);
		double c = cos(k * zc.y);
		double s = sin(k * zc.y);
		if (!fractal->transformCommon.functionEnabledOFalse)
		{
			zc.x = c * swap + -s * zc.y;
		}
		else
		{
			zc.z = c * swap + -s * zc.y;
		}
		zc.y = s * swap + c * zc.y;
	}

	if (fractal->transformCommon.rotationEnabled)
	{
		zc = fractal->transformCommon.rotationMatrix.RotateVector(zc);
	}

	double xFloor = fabs(zc.x - size * floor(zc.x / size + 0.5f));
	double yFloor = fabs(zc.y - size * floor(zc.y / size + 0.5f));
	double gridXY = min(xFloor, yFloor);

	if (!fractal->transformCommon.functionEnabledJFalse)
		grid = sqrt(gridXY * gridXY + zc.z * zc.z);
	else
		grid = max(fabs(gridXY), fabs(zc.z));

	aux.dist = min(aux.dist, (grid - fractal->transformCommon.offset0005) / (aux.DE + 1.0));*/
}
