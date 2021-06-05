
let $ = (s => document.querySelectorAll(s));
let top_panel = $("#top-panel")[0], block = $("#articles")[0], artCount = $("#art-count")[0], q = $("#q")[0];
let arts;

let USP = new URLSearchParams(location.search);
let keys = USP.getAll("q"), m = USP.get("m") || "OR";

if (keys.length) {
  for (let i = 0; i < keys.length; ++i)
    keys[i] = keys[i].toLowerCase();
  q.value = keys;
}


function checkArt(a) {
  if (keys.length == 0) return true;
  let cnt = 0;
  for (let i = 0; i < keys.length; ++i)
    if (a.title.toLowerCase().indexOf(keys[i]) != -1 || a.type.toLowerCase().indexOf(keys[i]) != -1 ||
      a.outline.toLowerCase().indexOf(keys[i]) != -1 || a.path.toLowerCase().indexOf(keys[i]) != -1)
      ++cnt;
  return m != "OR" ? (cnt == keys.length) : (cnt > 0);
}

function putArts() {
  function DateToHTML(d) {
    if ((typeof d) != "string") return "";
    let t = new Date(d);
    return `${t.getFullYear()}-${(t.getMonth() + 1).toString().padStart(2, '0')}-${t.getDate().toString().padStart(2, '0')} ` +
      `${t.getHours().toString().padStart(2, "0")}:${t.getMinutes().toString().padStart(2, "0")}`;
  }
  $("header>.title")[0].innerText = (keys.length > 0 ? "搜索结果" : "文章列表");
  let art_html = "", count = {};
  for (let i = arts.length - 1; i >= 0; --i) {
    arts[i].type = arts[i].path.split("/")[0];
    if (!checkArt(arts[i])) continue;
    if (count[arts[i].type]) ++count[arts[i].type];
    else count[arts[i].type] = 1;
    art_html += `<div class="card">` +
      `<div class="art-title"><a href="${arts[i].path}">${arts[i].title}</a></div>` +
      `<header class="art-meta">` + (
        `<span class="art-type">${arts[i].type}</span>` +
        `<span class="art-date">${DateToHTML(arts[i].date)}</span>`
      ) + `</header>` +
      `<div class="art-outline">${arts[i].outline}</div>` +
      `</div>`;
  }
  block.innerHTML = art_html;
  let countHtml = "";
  for (let i in count) {
    countHtml += `<div class="two-part"><div>${i}</div><div>${count[i]}</div></div>`;
  }
  artCount.innerHTML = countHtml;
  if (MathJax.typesetPromise) MathJax.typesetPromise(); else MathJax.startup.typeset = true;
}
fetch("list.json").then(r => r.json()).then(s => { arts = s; putArts(); });