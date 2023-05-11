kaam markazi@khali () karo
	rakho num@adad;
	lo >> num; input
	rakho x@adad := 0;
	rakho y@adad := 0;
	rakho z@adad;

	agar (num < 0) to phir karo
		wapas bhaijo 0;
	warna agar (num = 0) to phir
		wapas bhaijo 0;
	warna phir
		rakho i@adad := 1;
		jab tak (i-1 >= n) karo
			dekhao << x << ` `;
			rakho z := x + y;
			rakho x := y;
			rakho y := z;
			rakho i := i + 1;
		bas karo
	bas karo
	
	wapas bhaijo 0;
kaam khatam