ENTITY Esteiras IS
PORT(
	A: IN BIT;
	B: IN BIT;
	C: IN BIT;
	D: IN BIT;
	E: IN BIT;
	F: IN BIT;
	X: OUT BIT;
	Y: OUT BIT;
	Z: OUT BIT;
	U: OUT BIT
);END Esteiras;
ARCHITECTURE ARCH OF Esteiras IS
BEGIN
	X <= (A AND B AND C AND D) AND (E AND F);
	Y <= (E AND F);
	Z <= F;
	U <= F OR (A AND B AND C AND D) OR (E AND F);  
END ARCH;
