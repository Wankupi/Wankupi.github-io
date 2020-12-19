var MathJax = { startup: { typeset: true, output: 'chtml' }, tex: { inlineMath: [['$', '$'], ['\\(', '\\)']] }, options: { enableMenu: false } };

document.title += " | Wankupi";
function addCSS_wankupi(url) { let lnk = document.createElement("link"); lnk.rel = "stylesheet"; lnk.href = url; document.head.appendChild(lnk); }

addCSS_wankupi("/static/css/highlight.css");

(function () {
  let d = document.createElement("script");
  d.src = "/static/js/highlight/highlight.pack.js";
  d.async = true;
  d.addEventListener("load", e => { hljs.initHighlighting(); });
  document.head.appendChild(d);
})();

(function () {
  let d = document.createElement("script");
  d.src = "https://cdn.jsdelivr.net/npm/mathjax/es5/tex-chtml.js";
  d.async = true;
  document.head.appendChild(d);
})();

(function () {
  function loadValine() {
    new Valine({
      el: '#Comment',
      app_id: '0fXMSbCD7SIxO3z7u5j1VjkL-gzGzoHsz',
      app_key: 'eIi8ECHYotfQqPB4AQRI6nfi',
      placeholder: '写下你的精彩评论！',
      lang: 'zh-CN',
      visitor: false,
      recordIP: true,
      requiredFields: ['nick']
    });
  }
  let d = document.createElement("script");
  d.src = "https://cdn.jsdelivr.net/npm/valine/dist/Valine.min.js";
  d.async = true;
  d.addEventListener("load", loadValine);
  document.head.appendChild(d);
})();