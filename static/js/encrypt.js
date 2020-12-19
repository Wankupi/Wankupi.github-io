var bit = 35;
var mid = 'z';

function to4(s) {
  while (s.length < 4) s = '0' + s;
  return s;
}

function toUnicode(s) {
  let res = '';
  for (let i = 0; i < s.length; ++i) {
    let a = s.charCodeAt(i);
    res += `${mid}${a.toString(bit)}`;
  }
  return res;
}

function fromUnicode(s) {
  let ret = '';
  for (let i = 0; i < s.length;) {
    if (s[i] == mid) {
      let j = i + 1;
      while (j < s.length && s[j] != mid) ++j;
      let num = s.slice(i + 1, j);
      ret += String.fromCodePoint(parseInt(num, bit));
      // console.log(num, ' ', parseInt(num, 16), String.fromCodePoint(parseInt(num, 16)));
      i = j;
    } else ++i;
  }
  return ret;
}

function exchange(s, key) {
  const ch = '0123456789abcdefghijklmnopqrstuvwxyz';
  let p = {};
  for (let i = 0; i < 36; ++i)
    p[ch[i]] = key[i];
  let C = '';
  for (let i = 0; i < s.length; ++i)
    C += p[s[i]];
  return C;
}

function Encrypt(s, key) {
  if (key.length != 36) return;
  return exchange(toUnicode(s), key);
}

function Decrypt(s, key) {
  if (key.length != 36) return;
  return fromUnicode(exchange(s, key));
}