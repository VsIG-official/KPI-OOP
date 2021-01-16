# OOP

<p align="center">
  <img src="https://github.com/VsIG-official/KPI-OOP/blob/master/pict.png" data-canonical-src="https://github.com/VsIG-official/KPI-OOP/blob/master/pict.png" width="600" height="300" />
</p>

## Table of Contents

- [Description](#description)
- [Badges](#badges)
- [Contributing](#contributing)
- [License](#license)

### Description

This repo was created for subject "OOP" and have both labs and lectures

## Badges

> [![Theme](https://img.shields.io/badge/Theme-OOP-blue?style=flat-square)](https://en.wikipedia.org/wiki/Object-oriented_programming)
> [![Language](https://img.shields.io/badge/Language-C++-blue?style=flat-square)](https://en.wikipedia.org/wiki/C%2B%2B)
> [![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

---

## Example

```cpp
/// <summary>
/// Do something, when LB is unclicked
/// </summary>
/// <param name="hWnd"></param>
void MyEditor::OnLBup(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	X2 = pt.x;
	Y2 = pt.y;
	isPressed = false;
	pcshape[size]->Set(X1, Y1, X2, Y2);
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
	pcshape[size] = pcshape[size - 1]->Duplicate();
}
```

---

## Contributing

> To get started...

### Step 1

- 🍴 Fork this repo!

### Step 2

- **HACK AWAY!** 🔨🔨🔨

---

## License

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](http://badges.mit-license.org)

- **[MIT license](http://opensource.org/licenses/mit-license.php)**
- Copyright 2021 © <a href="https://github.com/VsIG-official" target="_blank">VsIG</a>.
