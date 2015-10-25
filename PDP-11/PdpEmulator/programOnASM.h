i - address Of Image in Memory
v - address of VideoBuffer
hI - height of Image
wI - width of Image
hS - height of Screen
wS - width of Screen
bW - border Width = (hS - hI) / 2
bH - border Height = (wS - wI) / 2

����� ����� ���������� �������� � ���������� �������
i = ������, ����� ������� ���������. ���� ����� ���������� ����� 1/2 �� ������
v = 040000
hI = wI = 
hS = wS = 
bW = bH = 
R5 for operation

// Start program
MOV #0, R0 // R0 - ������ � ��������
MOV #0, R1 // R1 - ������� � ��������
MOV #v, R2 // R2 - address in videobuffer
MOV #i, R3 // R3 - address of image
MOV #v, R4

// ��������� ������� ��������� ������ ������ �������� - upBytes, ������ ������ - upWords
MOV #0, R0
@0:
CMP R0, upWords
BEQ @1
MOV #0, (R2)+
ADD #020, R0
BR @0
@1:
MOV #0, R0
@7:
MOV #0, R1
CMP R0, hI
BE @2
@4:
CMP R1, bW
BGE @3
MOV #0, (R2)+
ADD #020, R1
BE @4
@3:
MOV #0, R5
ADD #wS, R5
SUB #bW, R5
CMP R1, R5
BGE @5
MOV (R3)+, (R2)+
ADD #020, R1
BE @3
@5:
MOV #0, R5
ADD #wS, R5
CMP R1, R5
BGE @6
MOV (R3)+ , (R2)+
ADD #020, R1
BE @5
@6:
ADD #01, R0
BE @7
@2:
// ��������� ������� ��������� ������ ����� �������� - bottomBytes, ������ ������ - bottomWords
MOV #0, R0
@8:
CMP R0, bottomWords
BEQ @9
MOV #0, (R2)+
ADD #020, R0
BR @8
@9:
// That's all