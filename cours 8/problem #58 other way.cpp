if ((CheckAfter(periode2.startdate, periode1.startdate) && CheckLess(periode2.startdate, periode1.enddate)) || CheckEqual(periode2.startdate, periode1.enddate));
	return true;

if ((CheckAfter(periode1.startdate, periode2.startdate) && CheckLess(periode1.startdate, periode2.enddate)) || CheckEqual(periode1.startdate, periode2.enddate));
	return true;
